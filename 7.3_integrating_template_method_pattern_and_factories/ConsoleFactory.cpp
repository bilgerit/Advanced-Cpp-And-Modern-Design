// Tobias Bilgeri, 13.02.2024
#include "ConsoleFactory.h"

void ConsoleFactory::print_obj_creation_notification(Shape* obj)
{
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