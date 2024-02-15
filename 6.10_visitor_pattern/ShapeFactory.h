// ShapeFactory ABC
// Tobias Bilgeri, 08.02.2024
#pragma once
#include "Point.h"
#include "Line.h"
#include "Circle.h"

class ShapeFactory {
    // ShapeFactory ABC
public:
    virtual ~ShapeFactory() {}
    virtual Circle* CreateCircle() = 0;
    virtual Line* CreateLine() = 0;
    virtual Point* CreatePoint() = 0;
};
