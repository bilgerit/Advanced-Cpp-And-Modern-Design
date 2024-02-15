// Line: Impl Shape
// Tobias Bilgeri, 13.02.2024
#pragma once
#include "Point.h"

class Line : public Shape
{
private:
	Point start_;
	Point end_;
public:
	Line() = default;
	Line(const double x1, const double y1, const double x2, const double y2);
	Line(const Point& p1, const Point& p2);
	~Line() override = default;
	std::string str() const override;
};