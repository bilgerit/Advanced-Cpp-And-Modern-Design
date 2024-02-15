// Simple examples of std::hash and boost::hash for a handful of data types.
// Tobias Bilgeri, 27.01.2024
#pragma once
#include <iostream>
#include <functional>
#include <limits>
#include <string>

#include <boost/functional/hash.hpp>

using Size_t = std::size_t;
using String = std::string;

// ex. a. two generic functions to hash arbitrary data types using Boost and C++11:
template <typename T>
Size_t boostHash(const T& key) {
    return boost::hash<T>()(key);
}

template <typename T>
Size_t cpp11Hash(const T& key) {
    return std::hash<T>()(key);
}

int main() {
    // ex. b. test the hash functions
    {
        int i = 111;
        const int* int_ptr = &i;
        String str = "Hello World";
        int maxInt = std::numeric_limits<int>::max();

        std::cout << "Boost hash: int: " << boostHash(i) << "\n";
        std::cout << "C++11 hash: int: " << cpp11Hash(i) << "\n\n";

        std::cout << "Boost hash: str: " << boostHash(str) << "\n";
        std::cout << "C++11 hash: str: " << cpp11Hash(str) << "\n\n";

        std::cout << "Boost hash: int_ptr: " << boostHash(int_ptr) << "\n";
        std::cout << "C++11 hash: int_ptr: " << cpp11Hash(int_ptr) << "\n\n";

        std::cout << "Boost hash: max int: " << boostHash(maxInt) << "\n";
        std::cout << "C++11 hash: max int: " << cpp11Hash(maxInt) << "\n\n";
    }

    // ex c. compute h1 ^ (h2 << 1)
    {
        String s1 = "QWERT";
        String s2 = "ASDFG";

        Size_t h1 = cpp11Hash(s1);
        Size_t h2 = cpp11Hash(s2);

        Size_t res = h1 ^ (h2 << 1);

        std::cout << "h1: " << h1 << "\n";
        std::cout << "h2: " << h2 << "\n";
        std::cout << "Result: " << res << "\n";
    }

    return 0;
}