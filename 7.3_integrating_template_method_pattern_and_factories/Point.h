// Point: Impl Shape
// Tobias Bilgeri, 13.02.2024
#pragma once
#include "Shape.h"

class Point : public Shape
{
private:
	double x = 0;
	double y = 0;
public:
	Point() = default;
	Point(double x, double y);
	~Point() override = default;
	std::string str() const override;
};