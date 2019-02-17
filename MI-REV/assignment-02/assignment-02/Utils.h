#pragma once

#include <windows.h>
#include <libloaderapi.h>

///
/// # Structures
///

// Represents storage for default implementations of memory management
// functions.
class Storage {
public:
	PIMAGE_THUNK_DATA mallocThunk;
	PIMAGE_THUNK_DATA callocThunk;
	PIMAGE_THUNK_DATA reallocThunk;
	PIMAGE_THUNK_DATA freeThunk;

	void* defaultMalloc = nullptr;
	void* defaultCalloc = nullptr;
	void* defaultRealloc = nullptr;
	void* defaultFree = nullptr;
};

// Represents memory operation, contains meta information about the operation.
class MemoryOperation {
public:
	// Pointer to allocated memory
	void* ptr = nullptr;
	// Size of allocated memory
	size_t size;
	// Indicates whether the data associated with this operation
	// were already deallocated
	bool deallocated = false;
};

///
/// # Memory tracking API
///

void* replaceCurrentThunkImplementation(PIMAGE_THUNK_DATA thunk, void* patchedImplementation);
MemoryOperation* readMemoryOperation(void* ptr);
void trackMemoryOperation(void* ptr, size_t size);

///
/// # Assignment API
///

void MallocDebug_Init();
void MallocDebug_Done();

void* MallocDebug_malloc(size_t size);
void* MallocDebug_calloc(size_t size, size_t count);
void* MallocDebug_realloc(void* block, size_t size);
void MallocDebug_free(void* block);

///
/// # Convenience API
///

typedef void* (*malloc_type)(size_t);
typedef void* (*calloc_type)(size_t, size_t);
typedef void* (*realloc_type)(void*, size_t);
typedef void(*free_type)(void*);
