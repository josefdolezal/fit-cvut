//
//  main.cpp
//  SSOString
//
//  Created by Josef Dolezal on 14/10/2018.
//  Copyright © 2018 Josef Dolezal. All rights reserved.
//

#include <iostream>
#include <string.h>

class String {
    char* data_;

public:
    String(const char* arg = ""): data_(new char[strlen(arg) + 1]) {
        strcpy(data_, arg);
    }

    String(const String&) = delete;
    String& operator=(const String&) = delete;
    ~String() { delete[] data_; }
    const char* data() const { return data_; }
};

namespace sso_buf {
    class String {
        char* data_;
        char buf_[8];

    public:
        String(const char* arg = "") {
            data_ = strlen(arg) < 8 ? buf_ : new char[strlen(arg) + 1];
            strcpy(data_, arg);
        }

        String(const String&) = delete;
        String& operator=(const String&) = delete;
        ~String() { if (data_ != buf_) delete[] data_; } const char* data() const { return data_; }
    };
}

namespace sso_tp {
    class String { char* data_;
        bool is_short() const { return reinterpret_cast<uintptr_t>(data_) & 1; }
        char* short_ptr() { return reinterpret_cast<char*>(&data_) + 1; }
        const char* short_ptr() const
            { return reinterpret_cast<const char*>(&data_) + 1; }

    public:
        String(const char* arg = "") {
            if (strlen(arg) < 7) {
                data_ = reinterpret_cast<char*>((uintptr_t)1); strcpy(short_ptr(), arg);
            } else {
                data_ = new char[strlen(arg) + 1];
                strcpy(data_, arg);
            }
        }

        String(const String&) = delete;
        String& operator=(const String&) = delete;
        ~String() { if (is_short() == false) delete[] data_; }
        const char* data() const { return is_short() ? short_ptr() : data_; }
    };
}

int main(int argc, const char * argv[]) {
    return 0;
}
