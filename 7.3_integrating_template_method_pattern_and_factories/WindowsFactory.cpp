// Tobias Bilgeri, 13.02.2024
#include "WindowsFactory.h"
void WindowsFactory::print_obj_creation_notification(Shape* obj)
{
	std::cout << "WindowsFactory: Created object " << obj->str() << "\n";
}

point_ptr WindowsFactory::CreatePoint()
{
	point_ptr new_point = std::make_unique<Point>(Point());
	print_obj_creation_notification(new_point.get());
	return new_point;
}
circle_ptr WindowsFactory::CreateCircle()
{
	circle_ptr new_circle = std::make_unique<Circle>(Circle());
	print_obj_creation_notification(new_circle.get());
	return new_circle;
}

std::tuple<point_ptr, line_ptr, circle_ptr> WindowsFactory::CreateAllShapes()
{
	return std::make_tuple(this->CreatePoint(), this->CreateLine(), this->CreateCircle());
}