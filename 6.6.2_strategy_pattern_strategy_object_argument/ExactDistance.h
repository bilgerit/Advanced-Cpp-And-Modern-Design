// ExactDistance Class
// DistanceStrategy implementation: Euclidian Distance
// Tobias Bilgeri, 8.2.2024
#pragma once
#include "DistanceStrategy.h"
#include "Point.h"

class ExactDistance : public DistanceStrategy {
public:
    double Distance(const Point& p1, const Point& p2) const override {
        double dx = p2.x() - p1.x();
        double dy = p2.y() - p1.y();
        return sqrt(dx * dx + dy * dy);
    }
    ~ExactDistance() override = default;
};