// Tobias Bilgeri, 13.02.2024
#include "Line.h"
Line::Line(const double x1, const double y1, const double x2, const double y2) : start_(x1, y1), end_(x2, y2) {}
Line::Line(const Point& p1, const Point& p2) : start_(p1), end_(p2) {}
std::string Line::str() const
{
	return "Line(start=" + start_.str() + ", end=" + end_.str() + ")";
}
