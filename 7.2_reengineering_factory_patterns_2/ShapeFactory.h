// Novel ShapeFactory
//
// Implemented with a runtime-policy based approach, whereby
// the 'Creator' methods can be set during runtime.
// Different policies can hence be implemented within this
// single base class without a need to create derived classes
// to implement differing policies.
//
// Tobias Bilgeri, 13.02.2024
#pragma once
#include <functional>

#include "Shape.h"
#include "Point.h"
#include "Line.h"
#include "Circle.h"

// define smart pointers used throughout this exercise to avoid memory leaks.
using point_ptr = std::unique_ptr<Point>;
using line_ptr = std::unique_ptr<Line>;
using circle_ptr = std::unique_ptr<Circle>;

// factory-method templates: function objects which obtain a unique_ptr to a specific object.
using point_creator = std::function<point_ptr()>;
using line_creator = std::function<line_ptr()>;
using circle_creator = std::function<circle_ptr()>;

class ShapeFactory
{
public:
	// Call Create-methods
	point_ptr PointCreator() const;
	line_ptr LineCreator() const;
	circle_ptr CircleCreator() const;

	// Set / Overwrite Create-methods
	void SetPointCreator(const point_creator& f);
	void SetLineCreator(const line_creator& f);
	void SetCircleCreator(const circle_creator& f);

private:
	point_creator PointCreator_;
	line_creator LineCreator_;
	circle_creator CircleCreator_;
};
