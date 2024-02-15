// ConsoleShapeFactory class
// Tobias Bilgeri, 08.02.2024
#pragma once
#include "ShapeFactory.h"

class ConsoleShapeFactory : public ShapeFactory {
public:
    ~ConsoleShapeFactory() = default;

    Circle* CreateCircle() override {
        double radius, x, y;
        std::cout << "Enter the central x coordiate: ";
        std::cin >> x;
        std::cout << "Enter the central y coordiate: ";
        std::cin >> y;
        std::cout << "Enter radius: ";
        std::cin >> radius;
        return new Circle(Point(x, y), radius);
    }

    Line* CreateLine() override {
        double x1, x2, y1, y2;
        std::cout << "Enter x1: ";
        std::cin >> x1;
        std::cout << "Enter x2: ";
        std::cin >> x2;
        std::cout << "Enter y1: ";
        std::cin >> y1;
        std::cout << "Enter y2: ";
        std::cin >> y2;
        return new Line(Point(x1, y1), Point(x2, y2));
    }

    Point* CreatePoint() override {
        double x, y;
        std::cout << "Enter x and y (seperated by space): ";
        std::cin >> x >> y;
        return new Point(x, y);
    }
};