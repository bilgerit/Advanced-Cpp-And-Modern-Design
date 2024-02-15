// Composite Pattern
// 
// ShapeComposite contains a list of pointers to Shape objects.
//
// Tobias Bilgeri, 9.2.2024
#pragma once
#include "ShapeComposite.h"
#include "Line.h"
#include "Circle.h"

void Print(const ShapeComposite& sc) {
    // print shape composite objects
    std::cout << "ShapeComposite: [";
    for (ShapeComposite::const_iterator it = sc.begin(); it != sc.end(); ++it) {
        std::cout << (*it)->to_string() << ", ";
    }
    std::cout << "]\n";
}

int main() {
    Point p(1.0, 1.0);
    Line l(p, Point(2.0, 2.0));
    Circle c(p, 3.0);

    ShapeComposite sc;
    sc.AddShape(&p);
    sc.AddShape(&l);
    sc.AddShape(&c);

    Print(sc);

    return 0;
}