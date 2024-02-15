// Strategy Pattern: Point Distance
// 
// In this exercise we implement a basic runtime strategy pattern, with the
// exception that we use a static member function such that the same strategy
// is used across all objects of type Point.
// Alternative designs would be: use non-static member, use function object
// using std::function, use compile-time strategy pattern, ...
// 
// Tobias Bilgeri, 8.02.2024
#include "DistanceStrategy.h"
#include "ExactDistance.h"
#include "ApproximateDistance.h"


int main() {

    Point p1(1.0, 1.0);
    Point p2(2.0, 2.0);

    // compute distance using default strategy
    std::cout << "Distance using default strategy: " << p1.Distance(p2) << std::endl;

	// set strategy  to ExactDistance
    Point::SetStrategy(new ExactDistance());
    std::cout << "Exact distance (Euclidian): " << p1.Distance(p2) << std::endl;

    // change strategy to ApproximateDistance
    Point::SetStrategy(new ApproximateDistance());
	std::cout << "Approximate distance (Manhatten): " << p1.Distance(p2) << std::endl;

    return 0;
}