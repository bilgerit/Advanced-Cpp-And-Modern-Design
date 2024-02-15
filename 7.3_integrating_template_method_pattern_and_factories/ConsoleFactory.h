// ConsoleFactory: Impl ShapeFactory
// Tobias Bilgeri, 13.02.2024
#pragma once
#include "ShapeFactory.h"

class ConsoleFactory : public ShapeFactory {
    // factory to create shapes based on manual console input
private:
    static void print_obj_creation_notification(Shape* obj);
public:
    ~ConsoleFactory() override = default;
    point_ptr CreatePoint() override;
    circle_ptr CreateCircle() override;
    std::tuple<point_ptr, line_ptr, circle_ptr> CreateAllShapes() override;
};