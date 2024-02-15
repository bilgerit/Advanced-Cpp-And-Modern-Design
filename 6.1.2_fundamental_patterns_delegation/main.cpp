// Delegation
//
// Point class implements calculation of distance between two points.
// Line class implements calculation of length of line, which is equivalent
// to distance between two points, and hence can be delegated to the Point class.
// 
// Tobias Bilgeri, 8.2.2024
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include <cassert>

int main() {
    Point p1(1.0, 1.0);
    Point p2(2.0, 2.0);
    Line l(p1, p2);

    // distance to origin of point
    std::cout << "distance from p1 to origin: " << p1.Distance() << std::endl;

    // distance between two points
	std::cout << "distance between p1 and p2: " << p1.Distance(p2) << std::endl;

    // length of line == distance between two points
    // ... implemented using delegation.
	std::cout << "length of line l: " << l.Length() << std::endl;

    // since we use delegation, these two must be exactly equal:
    assert(l.Length() == p1.Distance(p2));

    return 0;
}