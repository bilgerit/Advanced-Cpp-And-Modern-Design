// In this exercise, we create unordered STL sets with custom hash & comparison
// functors, as well as implement default hash & comparison operators for non-
// standard data types.
// We also created ordered STL sets.
// Finally, we time everything.
// 
// Exemplary timing result:
//   Duration for unordered multiset with default hash: 0.938267 s
//   Duration for unordered multiset with custom hash : 0.938631 s
//   Duration for standard(ordered) multiset : 1.17142 s
// 
// Tobias Bilgeri, 27.01.2024
#pragma once
#include <unordered_set>
#include <set>
#include <chrono>
#include <iostream>
#include <functional>
#include <boost/functional/hash.hpp>


// Simple custom struct
struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    // Default comparision operators
    bool operator < (const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }

    bool operator == (const Point& other) const {
        return x == other.x && y == other.y;
    }
};


// Ex. A. Default Hash
// Follwing the example on https://en.cppreference.com/w/cpp/utility/hash
// ... a custom specialization of std::hash can be injected in namespace std
// via template-specialisation:
template<>
struct std::hash<Point>
{
    std::size_t operator()(const Point& p) const noexcept
    {
        std::size_t h1 = std::hash<int>()(p.x);
        std::size_t h2 = std::hash<int>()(p.y);
        return h1 ^ (h2 << 1);
    }
};


// Ex. B. Non-Default Hash & Equality
// Just a callable struct that takes a Point-object and returns a size_t object.
struct CustomPointHash {
    // Custom hashing functor for points. Follows same logic as in Exercise 5.4.2.
    std::size_t operator()(const Point& pt) const {
        std::size_t seed = 0;
        boost::hash_combine(seed, pt.x);
        boost::hash_combine(seed, pt.y);
        return seed;
    }
};

struct CustomPointEqualityCheck {
    bool operator()(const Point& a, const Point& b) const {
        return a.x == b.x && a.y == b.y;
    }
};
    

int main() {
    const int N = 1000000; // Number of points to insert

    // ex. a. unordered multiset with default hash
    {
        auto start = std::chrono::high_resolution_clock::now();
        
        // create unordered multiset
        // since we only specify the Point-template parameter, it now uses
        // implicitly the default hashing of Point (which we had to specify
        // above) and default equality (which is a member method of Point).
        std::unordered_multiset<Point> points;
        for (int i = 0; i < N; ++i) {
            points.insert(Point(i, i));
        }
        
        // erase some point
        points.erase(Point(0, 0));

        // clear the multiset
        points.clear();

        // print duration
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << "Duration for unordered multiset with default hash: " << diff.count() << " s\n";
    }

    // ex. b. unordered multiset with custom hash and comparision
    {
        // same logic as in ex. a. except for the unordered_multiset initialization.
        auto start = std::chrono::high_resolution_clock::now();

        std::unordered_multiset<Point, CustomPointHash, CustomPointEqualityCheck> points;

        for (int i = 0; i < N; ++i) {
            points.insert(Point(i, i));
        }

        points.erase(Point(0, 0));
        points.clear();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << "Duration for unordered multiset with custom hash: " << diff.count() << " s\n";
    }

    // ex. c. standard (ordered) multiset
    {
        auto start = std::chrono::high_resolution_clock::now();

        std::multiset<Point> points;
        for (int i = 0; i < N; ++i) {
            points.insert(Point(i, i));
        }
        points.erase(Point(0, 0));
        points.clear();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << "Duration for standard (ordered) multiset: " << diff.count() << " s\n";
    }
    return 0;
}