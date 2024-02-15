// ShapeFactory ABC
// Tobias Bilgeri, 13.02.2024
#pragma once
#include "Shape.h"
#include "Point.h"
#include "Line.h"
#include "Circle.h"

using point_ptr = std::unique_ptr<Point>;
using line_ptr = std::unique_ptr<Line>;
using circle_ptr = std::unique_ptr<Circle>;

class ShapeFactory
{
public:
	virtual ~ShapeFactory() = 0;
	virtual point_ptr CreatePoint() = 0;
	virtual line_ptr CreateLine() = 0;
	virtual circle_ptr CreateCircle() = 0;
	virtual std::tuple<point_ptr, line_ptr, circle_ptr> CreateAllShapes() = 0;
};

