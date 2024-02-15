// Point class
// Tobias Bilgeri, 7.2.2024
#pragma once
#include "Shape.h"
#include <iostream>
#include <string>
#include "DistanceStrategy.h"

class Point: public Shape {
private:
    double mx, my;

public:
    static DistanceStrategy* mstrategy;

	Point();
    Point(double xs, double ys); 
    Point(const Point& pt);
    Point& operator=(const Point& pt);
    ~Point() override = default;
    double x() const;
    double y() const;
    void x(const double xs);
    void y(const double ys);

    std::string to_string() const override;

    double Distance(const Point& p) const;
    double Distance() const;

    Point* Clone() const override;
    static void SetStrategy(DistanceStrategy* s);
    double Distance(const Point& other, const DistanceStrategy& strategy) const;

    friend std::ostream& operator << (std::ostream& os, const Point& p);

    void Accept(ShapeVisitor& visitor) override;
};
