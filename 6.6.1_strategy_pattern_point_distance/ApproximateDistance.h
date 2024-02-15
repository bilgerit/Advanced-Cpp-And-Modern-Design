// ApproximateDistance Class
// DistanceStrategy implementation: Manhatten Metric
// Tobias Bilgeri, 8.2.2024
#pragma once
#include "DistanceStrategy.h"
#include "Point.h"

class ApproximateDistance : public DistanceStrategy {
public:
    double Distance(const Point& p1, const Point& p2) const override {
        return abs(p2.x() - p1.x()) + abs(p2.y() - p1.y());
    }
    ~ApproximateDistance() override = default;
};