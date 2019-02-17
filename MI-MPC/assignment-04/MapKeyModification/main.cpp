//
//  main.cpp
//  MapKeyModification
//
//  Created by Josef Dolezal on 27/11/2018.
//  Copyright © 2018 Josef Dolezal. All rights reserved.
//

#include <iostream>
#include <map>

class X {
    double d_;
public:
    X() : d_(0.0) { };
    X(double d) : d_(d) { std::cout << "converting: " << d << std::endl; }
    X(const X& other) : d_(other.d_) { std::cout << "copy: " << d_ << std::endl; }
    X(X&& other) : d_(other.d_) { std::cout << "move: " << d_ << std::endl; }
    operator double() const { return d_; }
};

namespace cpp14 {
    void replaceMapKey() {
        std::map<int, X> m1 = {{1, 1.0}, {-1, 2.0}, {3, 3.0}};
        std::map<int, X> m2 = {{4, 4.0}, {5, 5.0}};

        // Replace the node key
        m1.erase(m1.find(-1));
        m1.emplace(2, 2.0);

        // Merge maps
        m1.insert(std::make_move_iterator(m2.begin()), std::make_move_iterator(m2.end()));
    }
}

namespace cpp17 {
    void replaceMapKey() {
        std::map<int, X> m1 = {{1, 1.0}, {-1, 2.0}, {3, 3.0}};
        std::map<int, X> m2 = {{4, 4.0}, {5, 5.0}};

        // Update the node key
        auto handle = m1.extract(-1);
        handle.key() = 2;
        m1.insert(std::move(handle));

        // Merge maps
        m1.merge(m2);
    }
}

int main(int argc, const char * argv[]) {
    std::cout << "C++14" << std::endl;
    cpp14::replaceMapKey();

    std::cout << "C++17" << std::endl;
    cpp17::replaceMapKey();

    return 0;
}
