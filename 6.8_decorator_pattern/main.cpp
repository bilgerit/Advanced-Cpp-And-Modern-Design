// Decorator Pattern
// 
// Allows adding meta-information to an object.
// Here, we create a NameDecorator, which allows adding a name
// to a Shape object.
// 
// Tobias Bilgeri, 10.02.2024
#include <iostream>
#include "Circle.h"
#include "NameDecorator.h"


int main() {
    Circle circle = Circle(Point(1., 1.), 1.);

    // name decorator
    NameDecorator* namedCircle = new NameDecorator(&circle, "HelloWorld");
    std::cout << "circle name: " << namedCircle->GetName() << std::endl;
    std::cout << namedCircle->to_string() << std::endl;

    // try cloning
    NameDecorator* clonedCircle = static_cast<NameDecorator*>(namedCircle->Clone());
	std::cout << "circle name stored in cloned shape decorator: " << clonedCircle->GetName() << std::endl;

    return 0;
}