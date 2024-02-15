// Circle class
// Tobias Bilgeri, 7.2.2024
#pragma once
#include "Point.h"
#include <iostream>
#include <string>

class Circle: public Shape {
private:
    Point mcenter;
    double mradius;
public:
    Circle() = default;
    Circle(const Point& c, double r);
    Circle(const Circle& pt) = default;
    Circle& operator=(const Circle& pt) = default;
    ~Circle() override = default;
    Point CenterPoint() const;
    double Radius() const;
    void CenterPoint(const Point centre);
    void Radius(const double radius);

    std::string to_string() const override;
    Circle* Clone() const override;

    friend std::ostream& operator << (std::ostream& os, const Circle& c);
};