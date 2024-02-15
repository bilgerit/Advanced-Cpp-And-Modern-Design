// This file declares and defines the shape subtype Circle.
#pragma once
#include <tuple>
#include "Shape.h"

class Circle : public Shape {
private:
	double _radius;
	double _x;
	double _y;
public:
	using Shape::display;
	Circle() = default;
	Circle(double radius, double x, double y) : _radius(radius), _x(x), _y(y) {}
	~Circle() override = default;
	double radius() const { return _radius; }
	std::tuple<double, double> center() const { return std::make_tuple(_x, _y); }
	void display(IODevice& ioDevice) const override { ioDevice << *this; };
};