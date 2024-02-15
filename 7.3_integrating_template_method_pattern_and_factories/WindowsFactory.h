// WindowsFactory: Impl ShapeFactory
// Tobias Bilgeri, 13.02.2024
#pragma once
#include "ShapeFactory.h"

class WindowsFactory : public ShapeFactory
{
	// factory to create default-constructed shapes
private:
	static void print_obj_creation_notification(Shape* obj);
public:
	~WindowsFactory() override = default;

	point_ptr CreatePoint() override;
	circle_ptr CreateCircle() override;
	std::tuple<point_ptr, line_ptr, circle_ptr> CreateAllShapes() override;
};