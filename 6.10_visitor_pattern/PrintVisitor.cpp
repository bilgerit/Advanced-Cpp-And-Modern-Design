// Tobias Bilgeri, 11.02.2024
#include "PrintVisitor.h"
#include "Shape.h"
#include "Point.h"
#include "Circle.h"
#include "Line.h"
#include "NameDecorator.h"
#include "ShapeComposite.h"

void PrintVisitor::Visit(Point& point) {
    std::cout << "Visiting Point: " << point << "\n";
}
void PrintVisitor::Visit(Line& line) {
    std::cout << "Visiting Line: " << line << "\n";
}
void PrintVisitor::Visit(Circle& circle) {
    std::cout << "Visiting Circle: " << circle << "\n";
}

void PrintVisitor::Visit(ShapeComposite& composite) {
    std::cout << "Visiting ShapeComposite: " << "\n";
    for (Shape* element : composite.GetShapes()) {
        std::cout << "\t";
        element->Accept(*this);
    }
}

void PrintVisitor::Visit(NameDecorator& name_decorator) {
    std::cout << "Visiting NameDecorator: " << name_decorator.to_string() << "\n";
};
