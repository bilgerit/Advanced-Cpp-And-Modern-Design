// Tobias Bilgeri, 13.02.2024
#include "ShapeFactory.h"
ShapeFactory::~ShapeFactory() = default;
line_ptr ShapeFactory::CreateLine()
{
	point_ptr p1 = this->CreatePoint();
	point_ptr p2 = this->CreatePoint();
	return std::make_unique<Line>(Line(*p1.get(), *p2.get()));
}
