// NameDecorator implementation
// Tobias Bilgeri, 10.02.2024
#include "NameDecorator.h"

NameDecorator::NameDecorator() : ShapeDecorator(), _name("Default") {}
NameDecorator::NameDecorator(Shape* shape, const std::string& name) : ShapeDecorator(shape), _name(name) {}

std::string NameDecorator::GetName() const {
    return _name;
}

void NameDecorator::SetName(const std::string& name) {
    this->_name = name;
}

Shape* NameDecorator::Clone() const {
    return new NameDecorator(_shape, _name);
}

std::string NameDecorator::to_string() const {
    return "Shape " + this->GetName() + ": " + _shape->to_string();
}