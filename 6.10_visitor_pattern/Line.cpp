// Line class
// Tobias Bilgeri, 7.2.2024
#include "Line.h"

Line::Line(const Point& pt1s, const Point& pt2s) : mp1(pt1s), mp2(pt2s) {}

Point Line::p1() const { return mp1; }

Point Line::p2() const { return mp2; }

void Line::p1(const Point& ps) { mp1 = ps; }

void Line::p2(const Point& ps) { mp2 = ps; }

std::string Line::to_string() const {
    return "Line(" + this->p1().to_string() + ", " + this->p2().to_string() + ")";
}

Line* Line::Clone() const {
    return new Line(*this);
}

double Line::Length() const {
    // euclidian length of line implemented as distance between start and end point
    // DELEGATION: distance between two points is implemented in the point class.
	return p1().Distance(p2());
}

std::ostream& operator<<(std::ostream& os, const Line& l) {
    os << "Line(" << l.p1() << ", " << l.p2() << ")";
    return os;
}

void Line::Accept(ShapeVisitor& visitor) {
    visitor.Visit(*this);
}