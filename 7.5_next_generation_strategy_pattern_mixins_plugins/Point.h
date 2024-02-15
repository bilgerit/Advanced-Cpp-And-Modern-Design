// Point class
// 
// Simplified for demonstration purposes.
// 
// Tobias Bilgeri, 15.02.2024
#pragma once
#include "DistanceStrategy.h"

class Point
{
public:
	Point() = default;
	Point(const double x, const double y) : x_(x), y_(y){}
	double x() const { return x_; }
	double y() const { return x_; }


	double distance(const Point& other)
	{
		// compute distance between this and another point: state-full (as in: depends on the distance_strategy_ member variable)
		return distance_strategy_(*this, other);
	}

	double distance(const Point& other, const PointsDistanceAlgo& algo)
	{
		// compute distance between this and another point: state-less (as in: independent of the distance_strategy_ member variable)
		return algo(*this, other);
	}

	DistanceStrategy& get_distance_strategy()
	{
		// get the distance strategy
		// can be used to modify the distance strategy during runtime
		return distance_strategy_;
	}

private:
	double x_ = 0;
	double y_ = 0;
	DistanceStrategy distance_strategy_;
};

