// Variadic Hash Function: hash_value
// Implemented as a wrapper around boost::hash_combine.
// Tobias Bilgeri, 27.01.2024
#pragma once
#include <iostream>
#include <functional>
#include <boost/functional/hash.hpp>

template <typename T>
size_t hash_value(size_t seed, const T& arg) {
    // Take a seed and a hashable arg, and alter the seed using boost::hash_combine.
    // Acts as terminal call for variadic hash_combine function.
    boost::hash_combine(seed, arg);
    return seed;
}

template <typename T, typename ... Types>
size_t hash_value(size_t seed, const T& arg, const Types& ...args) {
    // variadic hashing.
    // variadic wrapper around hash_combine.
    boost::hash_combine(seed, arg);
    return hash_value<Types...>(seed, args...);
}

template <typename ... Types>
size_t hash_value(const Types& ...args) {
    // Get a hash value for a set of arguments of 
    // hashable (via boost::hash_combine) types.
    size_t seed = 0;
    return hash_value<Types...>(seed, args...);
}

int main() {
    size_t hash_val = hash_value("Hello World", 1, 2.3, true);
    std::cout << "Hash value: " << hash_val << std::endl;
    return 0;
}