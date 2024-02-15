// Circle class
// Tobias Bilgeri, 7.2.2024
#include "Circle.h"


Circle::Circle(const Point& c, double r) : mcenter(c), mradius(r) {}

Point Circle::CenterPoint() const { return mcenter; }

double Circle::Radius() const { return mradius; }

void Circle::CenterPoint(const Point centre) { mcenter = centre; }

void Circle::Radius(const double radius) { mradius = radius; }

std::string Circle::to_string() const {
	return "Circle(" + this->CenterPoint().to_string() + ", " + std::to_string(this->Radius()) + ")";
}

Circle* Circle::Clone() const {
    return new Circle(*this);
}

std::ostream& operator << (std::ostream& os, const Circle& c) {
    os << "Circle(" << c.CenterPoint() << ", " << c.Radius() << ")";
    return os;
}

void Circle::Accept(ShapeVisitor& visitor) {
    visitor.Visit(*this);
}
