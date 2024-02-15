// ShapeDecorator implementation
// Tobias Bilgeri, 10.02.2024
#include "ShapeDecorator.h"

ShapeDecorator::ShapeDecorator() : _shape(nullptr) {}

ShapeDecorator::ShapeDecorator(Shape* shape) : _shape(shape) {}

Shape* ShapeDecorator::GetShape() const {
    return _shape;
}

void ShapeDecorator::SetShape(Shape* shape) {
    this->_shape = shape;
}
