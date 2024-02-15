// Tobias Bilgeri, 13.02.2024
#include "Point.h"
Point::Point(double x, double y) : x(x), y(y) {}
std::string Point::str() const
{
	return "Point(x=" + std::to_string(x) + ", y=" + std::to_string(y) + ")";
}