// Shape abstract base class
// Tobias Bilgeri, 7.2.2024
#pragma once
#include <string>

class Shape
{
private:

public:
	Shape() = default;
	Shape(const Shape& shp) = default;
	Shape& operator = (const Shape& shp) = default;
	virtual ~Shape() = default;

	// Implementations of move operations not required in the exercise:
	//Shape(Shape&& shp) = default;
	//Shape& operator = (Shape&& shp) = default;

	// force some interface
	virtual std::string to_string() const = 0;
	virtual Shape* Clone() const = 0;
};