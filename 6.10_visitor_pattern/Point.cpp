// Point class
// Tobias Bilgeri, 7.2.2024
#include "Point.h"

#include <variant>

#include "OriginPoint.h"
#include "ExactDistance.h"

// initialize static member
DistanceStrategy* Point::mstrategy = new ExactDistance();

Point::Point() : mx(0.), my(0.) {};

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

double Point::Distance(const Point& p) const {
    return mstrategy->Distance(*this, p);

}

double Point::Distance() const {
    // euclidian distance to origin
    // old code with fixed origin: return std::sqrt(x() * x() + y() * y());
    // new code uses Singleton-Type OriginPoint.
    Point origin = *OriginPoint::instance();
    return Distance(origin);
}

Point* Point::Clone() const {
    return new Point(*this);
}

void Point::SetStrategy(DistanceStrategy* s) {
    mstrategy = s;
}

double Point::Distance(const Point& other, const DistanceStrategy& strategy) const {
    return strategy.Distance(*this, other);
}

std::ostream& operator << (std::ostream& os, const Point& p) {
    os << "Point(" << p.x() << ", " << p.y() << ")";
    return os;
}

void Point::Accept(ShapeVisitor& visitor) {
    visitor.Visit(*this);
}