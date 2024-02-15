// Singleton OriginPoint class.
// Tobias Bilgeri, 8.2.2024
#pragma once
#include "Singleton.hpp"
#include "Point.h"


class OriginPoint : public Singleton<Point> {
    // Singleton OriginPoint class.
private:
    Point morigin;

public:

    OriginPoint() = default;
    ~OriginPoint() = default;

    // don't allow copies and assignment
    OriginPoint(const OriginPoint& p) = delete;
    OriginPoint& operator = (const OriginPoint& p) = delete;
};