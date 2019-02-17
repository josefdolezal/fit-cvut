//
//  String.hpp
//  PIMPL
//
//  Created by Josef Dolezal on 31/10/2018.
//  Copyright © 2018 Josef Dolezal. All rights reserved.
//

#ifndef String_hpp
#define String_hpp

#include <stdio.h>

class String {
    class Impl;
    Impl* pimpl_;

public:
    // Default constructor
    String(const char* = "");
    // Copy constructor (KK)
    String(const String&);
    // Move constructor (PK)
    String(String&&) noexcept;

    // JPO (KPO + PPO)
    String& operator=(String) noexcept;

    const char* data() const;
    void swap(String &);

    ~String();
};

#endif /* String_hpp */
