// Point class
// Tobias Bilgeri, 7.2.2024
#pragma once
#include "Shape.h"
#include <iostream>
#include <string>

class Point: public Shape {
private:
    double mx, my;
public:
    Point() = default;
    Point(double xs, double ys); 
    Point(const Point& pt);
    Point& operator=(const Point& pt);
    ~Point() override = default;
    double x() const;
    double y() const;
    void x(const double xs);
    void y(const double ys);

    std::string to_string() const;

    friend std::ostream& operator << (std::ostream& os, const Point& p);
};