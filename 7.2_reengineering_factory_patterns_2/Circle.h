// Circle: Impl Shape
// Tobias Bilgeri, 13.02.2024
#pragma once
#include "Point.h"

class Circle : public Shape
{
private:
	Point center_;
	double radius_ = 0;
public:
	Circle() = default;
	Circle(const double x, const double y, const double radius);
	~Circle() override = default;
	std::string str() const override;
	void setRadius(double r);
};