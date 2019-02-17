//
//  String.cpp
//  PIMPL
//
//  Created by Josef Dolezal on 31/10/2018.
//  Copyright © 2018 Josef Dolezal. All rights reserved.
//

#include <utility>
#include <cstring>
#include <iostream>
#include "String.hpp"

class String::Impl {
    char* data_;

public:
    Impl(const char* arg): data_(new char[strlen(arg) + 1]) { strcpy(data_, arg); }
    Impl(const Impl& other): Impl(other.data()) { }
    Impl(Impl&& other) noexcept : data_(other.data_) {
        other.data_ = nullptr;
    }

    const char* data() const { return data_; }

    ~Impl() { delete[] data_; }
};

// Default constructor
String::String(const char* arg): pimpl_(new Impl(arg)) { }
// Copy constructor
String::String(const String& other): String(other.data()) { }
// Move constructor
String::String(String&& other) noexcept : pimpl_(new Impl(std::move(*other.pimpl_))) { }

// KPO + PPO
String& String::operator=(String other) noexcept {
    swap(other);

    return *this;
}

const char* String::data() const { return pimpl_->data(); }

void String::swap(String& other) {
    std::swap(pimpl_, other.pimpl_);
}

String::~String() { delete pimpl_; }

// Free func swap
void swap(String& lhs, String& rhs) {
    lhs.swap(rhs);
}
