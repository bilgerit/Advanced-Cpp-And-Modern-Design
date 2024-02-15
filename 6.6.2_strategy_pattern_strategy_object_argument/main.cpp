// Strategy object as method argument
// 
// In addition to setting the distance strategy as a static member, we can also
// explicitly pass it as an argument to the distance method.
//
// Advantage: Can specify distance method on a per-Distance-call-basis, rather than
//            having a uniform distance method across all objects.
//            It also makes it more transparent which method got used.
// Disadvantage: Need to write more code for possibly no benefit.
// 
// Tobias Bilgeri, 08.02.2024
#pragma once
#include "DistanceStrategy.h"
#include "ExactDistance.h"
#include "ApproximateDistance.h"


int main() {

    Point p1(1.0, 1.0);
    Point p2(2.0, 2.0);

    ExactDistance exact_distance;
    ApproximateDistance approximate_distance;

    // set strategy  to ExactDistance
    Point::SetStrategy(new ExactDistance());
    std::cout << "Exact distance (Euclidian): " << p1.Distance(p2, exact_distance) << std::endl;

    // change strategy to ApproximateDistance
    Point::SetStrategy(new ApproximateDistance());
    std::cout << "Approximate distance (Manhatten): " << p1.Distance(p2, approximate_distance) << std::endl;

    return 0;
}