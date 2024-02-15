// Factory Pattern
// 
// A simple factory implementation where we get inputs from
// the console and create Point, Line, and Circle objects.
// 
// Tobias Bilgeri, 10.02.2024
#pragma once
#include "ConsoleShapeFactory.h"


int main() {
    // test console shape factory
    ConsoleShapeFactory factory;

    // point
    Point* point = factory.CreatePoint();
    std::cout << *point << std::endl;

    // line
    Line* line = factory.CreateLine();
    std::cout << *line << std::endl;

    // circle
    Circle* circle = factory.CreateCircle();
    std::cout << *circle << std::endl;

    return 0;
}