// Tobias Bilgeri, 13.02.2024
#include "ConsoleFactory.h"

void ConsoleFactory::print_obj_creation_notification(Shape* obj)
{
    // print a notification stating on an object.
    std::cout << "ConsoleFactory: Created object " << obj->str() << "\n";
}

point_ptr ConsoleFactory::CreatePoint() {
    double x, y;
    std::cout << "Enter x and y (seperated by space): ";
    std::cin >> x >> y;
    point_ptr ans = std::make_unique<Point>(Point(x, y));
    print_obj_creation_notification(ans.get());
    return ans;
}

line_ptr ConsoleFactory::CreateLine() {
    double x1, x2, y1, y2;
    std::cout << "Enter x1: ";
    std::cin >> x1;
    std::cout << "Enter x2: ";
    std::cin >> x2;
    std::cout << "Enter y1: ";
    std::cin >> y1;
    std::cout << "Enter y2: ";
    std::cin >> y2;
    line_ptr ans = std::make_unique<Line>(Line(x1, y1, x2, y2));
    print_obj_creation_notification(ans.get());
    return ans;
}

circle_ptr ConsoleFactory::CreateCircle() {
    double radius, x, y;
    std::cout << "Enter the central x coordiate: ";
    std::cin >> x;
    std::cout << "Enter the central y coordiate: ";
    std::cin >> y;
    std::cout << "Enter radius: ";
    std::cin >> radius;
    circle_ptr ans = std::make_unique<Circle>(Circle(x, y, radius));
    print_obj_creation_notification(ans.get());
    return ans;
}

std::tuple<point_ptr, line_ptr, circle_ptr> ConsoleFactory::CreateAllShapes()
{
    return std::make_tuple(this->CreatePoint(), this->CreateLine(), this->CreateCircle());
}