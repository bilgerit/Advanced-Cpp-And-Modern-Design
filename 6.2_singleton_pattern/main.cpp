// Singleton Pattern
// 
// The Singleton in Singleton.hpp & .cpp has been provided.
// 
// Tobias Bilgeri, 8.2.2024
#include "OriginPoint.h"


int main() {
    // check default OriginPoint
    Point* origin = OriginPoint::instance();
    std::cout << "origin: " << *origin << std::endl;

    // compute distance to origin
    Point p(1.0, 1.0);
    std::cout << "distance from p to origin: " << p.Distance() << std::endl;

    // change the OriginPoint:
    origin->x(-1.);
    origin->y(-1.);
    std::cout << "Distance from p to new origin: " << p.Distance() << std::endl;

    return 0;
}