// ConsoleFactory: Impl ShapeFactory
// Tobias Bilgeri, 13.02.2024
#pragma once
#include "ShapeFactory.h"

class ConsoleFactory : public ShapeFactory
{
    // This factory creates shapes based on console input requested
    // from the user when it's methods are called.
private:
    static void print_obj_creation_notification(Shape* obj);
public:
    ~ConsoleFactory() override = default;
    point_ptr CreatePoint() override;
    line_ptr CreateLine() override;
    circle_ptr CreateCircle() override;
    std::tuple<point_ptr, line_ptr, circle_ptr> CreateAllShapes() override;
};