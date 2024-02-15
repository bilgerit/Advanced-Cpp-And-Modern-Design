// DistanceStrategy ABC
// Tobias Bilgeri, 8.2.2024
#pragma once
class Point;

class DistanceStrategy {
public:
    virtual ~DistanceStrategy() {}
    virtual double Distance(const Point& p1, const Point& p2) const = 0;
};