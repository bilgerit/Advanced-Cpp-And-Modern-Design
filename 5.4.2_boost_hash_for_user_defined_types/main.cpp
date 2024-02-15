// Hashing custom objects
// We create hashes of custom objects (such as Point, array<Point>, ...) by
// accessing it's primitive member variables (such as Point's (x,y) coordinates),
// hash those, and combining the individual hashes of the primitives to create
// one unique hash of the object.
// 
// Pretty much the same thing is done here: 
// https://www.boost.org/doc/libs/1_55_0/doc/html/hash/combine.html
//
//  Tobias Bilgeri, 27.01.2024
#pragma once
#include <iostream>
#include <functional>
#include <array>
#include <boost/functional/hash.hpp>


// --------------
// Custom Structs:
// --------------

struct Point {
    // Simple custom struct.
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}
};

struct LineSegment {
    // Simple custom struct. Composed of two Point type objects.
    Point p1;
    Point p2;

    LineSegment(Point p1, Point p2) : p1(p1), p2(p2) {}
};


// --------------
// Custom Hash Functions for Point and LineSegment.
// The custom hash functions make use of member variables to create the hashes.
// --------------

std::size_t hashPoint(const Point& p) {
    std::size_t seed = 0;
    boost::hash_combine(seed, p.x);
    boost::hash_combine(seed, p.y);
    return seed;
}

std::size_t hashLineSegment(const LineSegment& ls) {
    std::size_t seed = 0;
    boost::hash_combine(seed, hashPoint(ls.p1));
    boost::hash_combine(seed, hashPoint(ls.p2));
    return seed;
}

// Implement hash function as a callable struct.
// Note: I don't inherit from std::unary_funciton since it is depreciated in C++17.
struct PointHash {
    std::size_t operator()(const Point& pt) const {
        std::size_t seed = 0;
        boost::hash_combine(seed, pt.x);
        boost::hash_combine(seed, pt.y);
        return seed;
    }
};

int main() {
    // ex.a. test hash functions
    {
        Point p(1, 2);
        LineSegment ls(Point(1, 2), Point(3, 4));

        std::cout << "Hash of Point: " << hashPoint(p) << "\n";
        std::cout << "Hash of LineSegment: " << hashLineSegment(ls) << "\n";
    }

    // ex. b. compute hash of a array of points.
    //        follows same logic as before, whereby we use an initial seed and 
    //        boost::hash_combine to continuosly update the original seed.
    {
        std::array<Point, 4> points = {
            Point(1, 2),
            Point(3, 4),
            Point(5, 6),
            Point(7, 8)
        };

        std::size_t seed = 0;

        for (const auto& point : points) {
            boost::hash_combine(seed, hashPoint(point));
        }

        std::cout << "Hash of array of Points: " << seed << "\n";
    }

    // ex. c. hashing with the callable object.
    {
        Point p(1, 2);
        PointHash pointHash;
        std::cout << "Hash of Point w/ callable object: " << pointHash(p) << "\n";
    }

    return 0;
}