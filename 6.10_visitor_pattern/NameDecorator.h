// NameDecorator class
// Derived from the ShapeDecorator base class.
// ShapeDecorator holds a pointer to Shape object.
// The NameDecorator holds a string which can act as a name to the Shape object.
// Tobias Bilgeri, 10.02.2024
#pragma once
#include "ShapeDecorator.h"

class NameDecorator : public ShapeDecorator {
private:
    std::string _name;

public:
    ~NameDecorator() override = default;
    NameDecorator();
    NameDecorator(Shape* shape, const std::string& name);

    std::string GetName() const;
    void SetName(const std::string& name);

    Shape* Clone() const ;

    std::string to_string() const override;

    void Accept(ShapeVisitor& visitor) override;
};