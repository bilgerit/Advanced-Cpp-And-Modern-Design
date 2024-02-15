// DistanceStrategy Implementations
// Tobias Bilgeri, 14.02.2024
#include "DistanceStrategy.h"

double DistanceStrategy::operator () (const Point& p1, const Point& p2)
{
    // call the distance strategy to compute the distance.
    if (consider_data_)
    {
        data_ += 1;
        std::cout << " (DistanceStrategy: Updated internal state to: " << data_ << ") ";
    }

    return distance_algo_(p1, p2);
}

void DistanceStrategy::set_distance_algo(const PointsDistanceAlgo& a)
{
    // allow dynamically changing the distance algorithm
    distance_algo_ = a;
}

void DistanceStrategy::set_consider_data(const bool b)
{
    // allow enabling / disabling updating of internal state when calling
    // a strategy.
    //
    // for demonstration purposes only
    // this implementation shows that it is very easy to
    // handle additional state;
    // of course, we could also implement a flexible state-updating-method
    // via function objects or similar.
    consider_data_ = b;
}