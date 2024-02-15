// ShapeVisitor ABC
// Tobias Bilgeri, 11.02.2024
#pragma once
class Shape;
class Point;
class Line;
class Circle;
class ShapeComposite;
class NameDecorator;

class ShapeVisitor {
public:
    virtual ~ShapeVisitor() {}
    virtual void Visit(Point& point) = 0;
    virtual void Visit(Line& line) = 0;
    virtual void Visit(Circle& circle) = 0;
    virtual void Visit(ShapeComposite& composite) = 0;
    virtual void Visit(NameDecorator& name_decorator) = 0;
};