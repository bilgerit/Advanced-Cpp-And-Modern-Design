// Pattern / Mixins / Plugins
//
// We replace a tradition ABC + derived class pattern with a single
// functor whose behaviour can be specialized by passing std::functional
// objects (lambdas herein) instead of using different derived classes.
// In this case, we apply this pattern to a DistanceStrategy to compute distances
// between points.
//
// This allows to not define a complex inheritance tree to implement
// differing strategies but instead to just pass callables such as lambdas
// or functors to implement different behaviour, as long as they satisfy
// the function template std::function<double(const Point&, const Point&)>.
//
// Furthermore, we implement stateful (=dependent on Point-object's strategy
// member variable) and stateless (we must pass the strategy as function argument)
// distance calculating member method for Point.
//
// Since DistanceStrategy itself is a function object, it can itself have
// dynamic state. We demonstrate this herein by giving it a counter
// which we can selective choose to update using the .set_consider_data(bool)
// method of the DistanceStrategy.
//
// Tobias Bilgeri, 14.02.2024
#include <iostream>
#include <cmath>

#include "Point.h"

// Two possible distance algorithm implementations:
PointsDistanceAlgo euclidian_dist = [](const Point& a, const Point& b) -> double {
    double dx = a.x() - b.x();
    double dy = a.y() - b.y();
    return std::sqrt(dx * dx + dy * dy);
    };

PointsDistanceAlgo manhatten_dist = [](const Point& a, const Point& b) -> double {
    return std::abs(a.x() - b.x()) + std::abs(a.y() - b.y());
    };


int main() {
    Point p1(1., 1.);
    Point p2(2., 2.);

    // euclidian dist
    std::cout << "euclidian dist, stateless (as in: strategy must get passed as argument): " << p1.distance(p2, euclidian_dist) << "\n";
    p1.get_distance_strategy().set_distance_algo(euclidian_dist);
    std::cout << "euclidian dist, stateful (as in: strategy is given by distance_strategy_ member variable): " << p1.distance(p2) << "\n";

    // manhatten dist
    std::cout << "manhatten dist, stateless (as in: strategy must get passed as argument): " << p1.distance(p2, manhatten_dist) << "\n";
    p1.get_distance_strategy().set_distance_algo(manhatten_dist);
    std::cout << "manhatten dist, stateful (as in: strategy is given by distance_strategy_ member variable): " << p1.distance(p2) << "\n";

    // case where the algorithm needs to hold some data:
    // tell the strategy to consider and update the internal data
    p1.get_distance_strategy().set_consider_data(true);
    // now call strategy again. Data will be updated.
    std::cout << "manhatten dist, stateful, w/ strategy object's state being updated: " << p1.distance(p2) << "\n";
    std::cout << "manhatten dist, stateful, w/ strategy object's state being updated: " << p1.distance(p2) << "\n";
    std::cout << "manhatten dist, stateful, w/ strategy object's state being updated: " << p1.distance(p2) << "\n";

    return 0;
}