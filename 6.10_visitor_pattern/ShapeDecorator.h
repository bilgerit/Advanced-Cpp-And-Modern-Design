// (Virtual) ShapeDecorator class
// Wraps around a Shape (ABC) pointer.
// Tobias Bilgeri, 10.02.2024
#pragma once
#include "Shape.h"

class ShapeDecorator : public Shape {
protected:
    Shape* _shape;

public:
    ShapeDecorator();
    ShapeDecorator(Shape* shape);

    Shape* GetShape() const;
    void SetShape(Shape* shape);
};