// This file declares and defines the shape subtype Line.
#pragma once
#include <tuple>
#include "Shape.h"

class Line : public Shape {
private:
	double _x1;
	double _y1;
	double _x2;
	double _y2;
public:
	Line() = default;
	Line(double _x1, double _y1, double _x2, double _y2) : _x1(_x1), _y1(_y1), _x2(_x2), _y2(_y2) {}
	~Line() override = default;
	std::tuple<double, double, double, double> coordinates() const { return std::make_tuple(_x1, _y1, _x2, _y2); }
	void display(IODevice& ioDevice) const override { ioDevice << *this; }
};