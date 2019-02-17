//
//  main.cpp
//  PIMPL
//
//  Created by Josef Dolezal on 31/10/2018.
//  Copyright © 2018 Josef Dolezal. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <utility>
#include "String.hpp"

void testDefaultConstructor();
void testStringCopyCtor();
void testStringMoveCtor();
void testAssignmentOpCopyCtor();
void testAssignmentOpMoveCtor();

int main(int argc, const char * argv[]) {
    testDefaultConstructor();

    testStringCopyCtor();
    testStringMoveCtor();

    testAssignmentOpCopyCtor();
    testAssignmentOpMoveCtor();

    return 0;
}

void testDefaultConstructor() {
    char str[] = "default ctor";
    String original(str);

    assert(strcmp(str, original.data()) == 0);
}

void testStringCopyCtor() {
    char str[] = "some string";
    String* original = new String(str);
    String* copy = new String(*original);

    // Test copy constructor
    assert(strcmp(original->data(), copy->data()) == 0);

    // Data should copied, free original memory and test copy
    delete original;
    assert(strcmp(copy->data(), str) == 0);

    // Cleanup
    delete copy;
}

void testStringMoveCtor() {
    char str[] = "copy test";
    String* original = new String(str);
    // Use the move constructor
    String* copy = new String(std::move(*original));

    // Test the move contructor
    assert(original->data() == nullptr);
    assert(strcmp(copy->data(), str) == 0);

    // Cleanup
    delete original;
    delete copy;
}

void testAssignmentOpCopyCtor() {
    char str[] = "assignment op copy ctor";
    String* original = new String(str);
    String assigned("");

    // Test assignment operator (calls copy ctor)
    assigned = *original;
    delete original;

    assert(strcmp(assigned.data(), str) == 0);
}

void testAssignmentOpMoveCtor() {
    char str[] = "assignment op move ctor";
    String* original = new String(str);
    String assigned("");

    // Test assignment operator (calls move ctor)
    assigned = std::move(*original);
    delete original;

    assert(strcmp(assigned.data(), str) == 0);
}
