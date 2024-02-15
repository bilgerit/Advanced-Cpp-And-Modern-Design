// Shape Hierarchy
//
// Typical Shape (=base) and Point/Line/Circle (derived) hierarchy.
// Line and Circle additionally store Point(s) (composition).
// 
// Tobias Bilgeri, 7.01.2024
#include <iostream>
#include "Shape.h"
#include "Point.h"
#include "Line.h"
#include "Circle.h"


int main() {
    // print a Point, Line, and Circle object.
    Point p(1., 2.);
    Line l(Point(1.0, 2.), Point(3., 4.));
    Circle c(Point(1., 2.), 5.0);

	std::cout << p << std::endl;
	std::cout << l << std::endl;
	std::cout << c << std::endl;

    return 0;
}