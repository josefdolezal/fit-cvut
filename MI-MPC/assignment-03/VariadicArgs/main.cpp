//
//  main.cpp
//  VariadicArgs
//
//  Created by Josef Dolezal on 07/11/2018.
//  Copyright © 2018 Josef Dolezal. All rights reserved.
//

#include <iostream>

///
/// AdjacentEqual
///

template <typename T, typename TT>
bool AdjacentEqual(const T& l, const TT& r) {
    return l == r;
}

template <typename T, typename TT, typename TTT, typename... Ts>
bool AdjacentEqual(const T& l, const TT& r, const TTT& n, const Ts&... ts) {
    return l == r || AdjacentEqual(r, n, ts...);
}

///
/// LRValues
///

std::pair<int, int>operator +(const std::pair<int,int>& lhs, const std::pair<int, int>& rhs) {
    return std::make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

std::pair<int, int> LRValues() {
    return std::make_pair(0, 0);
}

/// Lvalue
template <typename T>
std::pair<int, int> LRValues(T& t) {
    return std::make_pair(1, 0);
}


/// Rvalue
template <typename T>
std::pair<int, int> LRValues(T&& t) {
    return std::make_pair(0, 1);
}

template <typename T, typename TT>
std::pair<int, int> LRValues(T&& t, const TT&& tt) {
    return LRValues(std::forward<T>(t)) + LRValues(std::forward<TT>(tt));
}

template <typename T, typename... Ts>
std::pair<int, int> LRValues(T&& t, Ts&&... ts) {
    return LRValues(std::forward<T>(t)) + LRValues(std::forward<Ts>(ts)...);
}

///
/// AnyEqual
///

template<typename T, typename TT>
bool OneEqual(const T& t, const TT& tt) {
    return t == tt;
}

template<typename T, typename TT, typename TTT, typename... Ts>
bool OneEqual(const T& t, const TT& tt, const TTT& ttt, const Ts&&... ts) {
    return OneEqual(t, tt) || OneEqual(t, ttt, ts...);
}

template<typename T, typename TT>
bool AnyEqual(const T& t, const TT& tt) {
    return OneEqual(t, tt);
}

template<typename T, typename TT, typename TTT, typename... Ts>
bool AnyEqual(const T& t, const TT& tt, const TTT& ttt, const Ts&&... ts) {
    return OneEqual(t, tt) || OneEqual(t, ttt, ts...) || AnyEqual(tt, ttt, ts...);
}

///
/// Usage
///

int main(int argc, const char * argv[]) {
    std::cout << AdjacentEqual(1, 1.0);
    std::cout << AdjacentEqual(1, 2, 1.0, 3);
    std::cout << AdjacentEqual(1, 2, 1.0, 3, 3.0);
    std::cout << AdjacentEqual(false, 1);
    std::cout << AdjacentEqual(false, 1, true);
    std::cout << AdjacentEqual(std::string("hello"), std::string("hello"));
    std::cout << AdjacentEqual(std::string("hello"), std::string("world"));
    std::cout << AdjacentEqual('a', 0x61);

    std::cout << AnyEqual(1, 2, 1, 3);

    int i;
    double d;
    std::pair<int, int> p = LRValues(1, i, 2.0, i + 1, d);
    std::cout << p.first << ", " << p.second << std::endl;
}
