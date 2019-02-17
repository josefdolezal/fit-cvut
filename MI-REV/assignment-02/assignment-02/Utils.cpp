#include "pch.h"
#include "Utils.h"
#include <iostream>

///
/// # Shared resources
///

Storage storage;
const int MAXIMUM_OPERATIONS_ALLOWED = 100;
int operationsCount = 0;
MemoryOperation operations[MAXIMUM_OPERATIONS_ALLOWED];

///
/// # Memory tracking API
///

// Replaces the current implementation of function in given thunk.
// Returns pointer to the original implementation.
void* replaceCurrentThunkImplementation(PIMAGE_THUNK_DATA thunk, void* patchedImplementation) {
	MEMORY_BASIC_INFORMATION symbolMemoryInfo;
	unsigned long oldProtection;
	void * currentImplementation;

	// Get virtual address information for thunk being overriden
	VirtualQuery(thunk, &symbolMemoryInfo, sizeof(MEMORY_BASIC_INFORMATION));
	// Turn off the memory protection for symbol
	VirtualProtect(symbolMemoryInfo.BaseAddress, symbolMemoryInfo.RegionSize, PAGE_EXECUTE_READWRITE, &oldProtection);
	// Backup address of original symbol address
	currentImplementation = (void*)(unsigned long)thunk->u1.Function;
	// Replace the symbol
	thunk->u1.Function = (unsigned long)patchedImplementation;
	// Turn on the protection again
	VirtualProtect(symbolMemoryInfo.BaseAddress, symbolMemoryInfo.RegionSize, oldProtection, &oldProtection);

	return currentImplementation;
}

// Lookups given memory pointer in list of memory operations. Returns
// mutable reference to this operation. Fallbacks to 'nullptr' for unknown memory.
// If the the pointer is in operation but was deallocated, fallback to 'nullptr'.
MemoryOperation* readMemoryOperation(void* ptr) {
	for (int i = 0; i < operationsCount; ++i)
		if (operations[i].ptr == ptr && !operations[i].deallocated)
			return &operations[i];

	// Fallback for unknown memory pointer.
	return nullptr;
}

// Tracks memory operation for given pointer of given size.
void trackMemoryOperation(void* ptr, size_t size) {
	// Do not track operation if number of operations exceeded
	if (operationsCount >= MAXIMUM_OPERATIONS_ALLOWED) {
		printf("Warning: You exceeded maximum allowed number of tracked operations. All following memory operations will not be tracked.\n");
		return;
	}

	// Do not track operation for 'nullptr's, since it indicates that the allocation failed
	if (ptr == nullptr) {
		printf("Warning: Memory allocation (malloc, callor or realloc) failed");
		return;
	}

	// Set operation values
	operations[operationsCount].ptr = ptr;
	operations[operationsCount].size = size;
	operations[operationsCount].deallocated = false;

	// Track the operation
	operationsCount++;
}

///
/// # Assignment API
///

// Loads module header, replaces imported memory management functions
// with custom 'MallocDebug_<old_function>' alternatives. You always have to call
// 'MallocDebug_Done' before calling this function multiple times. Uses 'storage' for keeping
// the references to the original implementation.
void MallocDebug_Init() {
	HMODULE hPEFile = GetModuleHandle(NULL);
	// Get Dos and NT headers
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)hPEFile;
	PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((BYTE*)pDosHeader) + pDosHeader->e_lfanew);

	PIMAGE_IMPORT_DESCRIPTOR pImports = (PIMAGE_IMPORT_DESCRIPTOR)(((BYTE*)pDosHeader) + pNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	PIMAGE_IMPORT_DESCRIPTOR pImportsEnd = (PIMAGE_IMPORT_DESCRIPTOR)(((BYTE*)pImports) + pNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size);

	// Traverse over the list of linked DDLs
	for (; pImports < pImportsEnd && pImports->OriginalFirstThunk != NULL; ++pImports) {
		PIMAGE_THUNK_DATA pSymbolData = (PIMAGE_THUNK_DATA)(((BYTE*)pDosHeader) + pImports->OriginalFirstThunk);
		PIMAGE_THUNK_DATA pSymbolAddress = (PIMAGE_THUNK_DATA)(((BYTE*)pDosHeader) + pImports->FirstThunk);

		// We only support debugging for programs compiled using Visual Studio
		// which imports memory management functions from 'ucrtbased.dll' module.
		char* ddlName = (char*)((BYTE*)pDosHeader + pImports->Name);
		if (strcmp("ucrtbased.dll", ddlName) != 0) continue;

		// Traverse over the list of symbols from library
		for (; pSymbolData->u1.AddressOfData != NULL; ++pSymbolData, pSymbolAddress++) {
			PIMAGE_IMPORT_BY_NAME pImport = (PIMAGE_IMPORT_BY_NAME)(((BYTE*)pDosHeader) + pSymbolData->u1.AddressOfData);

			// For all memory management symbols
			if (strcmp("malloc", pImport->Name) == 0) {
				storage.mallocThunk = pSymbolAddress;
				storage.defaultMalloc = replaceCurrentThunkImplementation(storage.mallocThunk, MallocDebug_malloc);
			}
			else if (strcmp("calloc", pImport->Name) == 0) {
				storage.callocThunk = pSymbolAddress;
				storage.defaultCalloc = replaceCurrentThunkImplementation(storage.callocThunk, MallocDebug_calloc);
			}
			else if (strcmp("realloc", pImport->Name) == 0) {
				storage.reallocThunk = pSymbolAddress;
				storage.defaultRealloc = replaceCurrentThunkImplementation(storage.reallocThunk, MallocDebug_realloc);
			}
			else if (strcmp("free", pImport->Name) == 0) {
				storage.freeThunk = pSymbolAddress;
				storage.defaultFree = replaceCurrentThunkImplementation(storage.freeThunk, MallocDebug_free);
			}
		}
	}
}

// Restores original implementation of memory management functions
void MallocDebug_Done() {
	// Restore the default implementation (if available)
	if (storage.defaultMalloc != nullptr)
		replaceCurrentThunkImplementation(storage.mallocThunk, storage.defaultMalloc);
	if (storage.defaultCalloc != nullptr)
		replaceCurrentThunkImplementation(storage.callocThunk, storage.defaultCalloc);
	if (storage.defaultRealloc != nullptr)
		replaceCurrentThunkImplementation(storage.reallocThunk, storage.defaultRealloc);
	if (storage.defaultFree != nullptr)
		replaceCurrentThunkImplementation(storage.freeThunk, storage.defaultFree);

	// Cleanup operations tracking
	for (int i = 0; i < operationsCount; ++i) {
		// If the memory was not deallocated, print warning
		if (!operations[i].deallocated)
			printf("Warning: Memory at adress %p of size %u bytes was not deallocated. Possible memory leak.\n", operations[i].ptr, operations[i].size);

		// Set operation to default state
		operations[i].deallocated = false;
		operations[i].size = 0;
		operations[i].ptr = nullptr;
	}

	// Reset operations counter
	operationsCount = 0;
}

void* MallocDebug_malloc(size_t size) {
	// Use default malloc for memory allocation
	void * ptr = ((malloc_type)storage.defaultMalloc)(size);
	// Add record of memory allocation
	trackMemoryOperation(ptr, size);
	// Return allocated memory
	return ptr;
}

void* MallocDebug_calloc(size_t size, size_t count) {
	// Allocate the array
	void* ptr = ((calloc_type)storage.defaultCalloc)(size, count);
	// Track the allocation
	trackMemoryOperation(ptr, size * count);
	// Return pointer to allocated memory
	return ptr;
}

void* MallocDebug_realloc(void* block, size_t size) {
	// Try to find pointer in list of memory allocations
	MemoryOperation* operation = readMemoryOperation(block);
	// Allocate new memory
	void* ptr = ((realloc_type)storage.defaultRealloc)(block, size);

	// Mark old memory operation as deallocated only if the reallocation was successfull
	if (operation != nullptr && ptr != nullptr)
		operation->deallocated = true;
	else printf("Warning: Unknown memory segment %p is being reallocated. This memory is unknown or was previously deallocated.", block);

	// Track new memory
	trackMemoryOperation(ptr, size);

	return ptr;
}

void MallocDebug_free(void* block) {
	// Try to find memory operation for given pointer
	MemoryOperation* operation = readMemoryOperation(block);

	// If we found the operation, mark it as freed
	if (operation != nullptr)
		operation->deallocated = true;
	else printf("Warning: Unknown memory segment %p is being deallocated. This memory is unknown or was previously deallocated.", block);

	// Use default memory deallocation
	return ((free_type)storage.defaultFree)(block);
}
