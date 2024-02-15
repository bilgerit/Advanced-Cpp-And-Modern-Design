// Tobias Bilgeri, 13.02.2024
#include "Circle.h"
Circle::Circle(const double x, const double y, const double radius) : center_(x, y), radius_(radius) {}
std::string Circle::str() const
{
	return "Circle(center=" + center_.str() + ", radius=" + std::to_string(radius_) + ")";
}
void Circle::setRadius(double r)
{
	radius_ = r;
};
