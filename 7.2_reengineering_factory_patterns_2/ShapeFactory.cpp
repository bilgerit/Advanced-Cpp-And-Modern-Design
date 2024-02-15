// Tobias Bilgeri, 13.02.2024
#include "ShapeFactory.h"

point_ptr ShapeFactory::PointCreator() const { return PointCreator_(); }
line_ptr ShapeFactory::LineCreator() const { return LineCreator_(); }
circle_ptr ShapeFactory::CircleCreator() const { return CircleCreator_(); }

void ShapeFactory::SetPointCreator(const point_creator& f) { PointCreator_ = f; }
void ShapeFactory::SetLineCreator(const line_creator& f) { LineCreator_ = f; }
void ShapeFactory::SetCircleCreator(const circle_creator& f) { CircleCreator_ = f; }
