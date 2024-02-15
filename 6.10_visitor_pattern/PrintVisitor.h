// PrintVisitor class
// Tobias Bilgeri, 11.02.2024
#pragma once
#include "ShapeVisitor.h"

class PrintVisitor : public ShapeVisitor {
public:
    ~PrintVisitor() override = default;
    void Visit(Point& point) override;
    void Visit(Line& line) override;
    void Visit(Circle& circle) override;
    void Visit(ShapeComposite& composite) override;
    void Visit(NameDecorator& name_decorator) override;
};