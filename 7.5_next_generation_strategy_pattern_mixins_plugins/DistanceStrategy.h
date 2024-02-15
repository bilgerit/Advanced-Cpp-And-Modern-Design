// DistanceStrategy
//
// As demanded in the exercise, rather than having a DistanceStrategy ABC
// and using inheritance to create specific implementations such as
// ApproxDistance and ExactDistance, we instead create a single
// DistanceStrategy class, don't use any inheritance, and instead
// use std::function to assign function objects at runtime to
// allow for different behaviour.
//
// Tobias Bilgeri, 14.02.2024
#pragma once
#include <functional>
#include <iostream>

class Point;

// Distance Calculation Interface modelled as a Function Wrapper:
using PointsDistanceAlgo = std::function<double(const Point&, const Point&)>;


class DistanceStrategy
{
public:
    DistanceStrategy() = default;

    double operator () (const Point& p1, const Point& p2);
    void set_distance_algo(const PointsDistanceAlgo& a);
    void set_consider_data(const bool b);

private:
    PointsDistanceAlgo distance_algo_;
    bool consider_data_ = false;
    int data_ = 0;
};
