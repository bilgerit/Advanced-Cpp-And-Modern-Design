// Line class
// Tobias Bilgeri, 7.2.2024
#pragma once
#include "Point.h"
#include <iostream>
#include <string>

class Line: public Shape {
private:
    Point mp1, mp2;
public:
    Line() = default;
    Line(const Point& pt1s, const Point& pt2s); 
    Line(const Line& pt) = default;
    Line& operator=(const Line& pt) = default;
    ~Line() override = default;
    Point p1() const;
    Point p2() const;
    void p1(const Point& ps); 
    void p2(const Point& ps);

    std::string to_string() const override;
    Line* Clone() const override;

    double Length() const;

    friend std::ostream& operator<<(std::ostream& os, const Line& l);

    void Accept(ShapeVisitor& visitor) override;
};