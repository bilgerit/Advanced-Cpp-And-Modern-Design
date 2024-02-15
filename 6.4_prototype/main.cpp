// Prototype pattern
// Herein we implement Clone() methods in objects.
// Tobias Bilgeri, 05.01.2024
#pragma once
#include "Circle.h"
#include "Line.h"
#include "Point.h"
#include "ShapeComposite.h"


int main() {
    // try cloning Point, List, Circle, and ShapeComposite type objects.
    Point p(1.0, 1.0);
    Line l(p, Point(2.0, 2.0));
    Circle c(p, 3.0);

    ShapeComposite sc1;
    sc1.AddShape(p.Clone());
    sc1.AddShape(l.Clone());
    sc1.AddShape(c.Clone());
    Print(sc1);

    const auto sc3 = sc1.Clone();
    Print(*sc3);
    delete sc3;

    return 0;
}