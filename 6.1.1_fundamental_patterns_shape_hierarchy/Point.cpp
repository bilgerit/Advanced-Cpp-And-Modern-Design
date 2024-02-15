// Point class
// Tobias Bilgeri, 7.2.2024
#include "Point.h"

Point::Point(double xs, double ys) : mx(xs), my(ys) {}

Point::Point(const Point& pt) : mx(pt.mx), my(pt.my) {}

Point& Point::operator=(const Point& pt) {
    mx = pt.mx;
    my = pt.my;
    return *this;
}

double Point::x() const { return mx; }

double Point::y() const { return my; }

void Point::x(const double xs) { mx = xs; }

void Point::y(const double ys) { my = ys; }

std::string Point::to_string() const {
    return "Point(" + std::to_string(x()) + ", " + std::to_string(y()) + ")";
}


std::ostream& operator << (std::ostream& os, const Point& p) {
    os << "Point(" << p.x() << ", " << p.y() << ")";
    return os;
}
