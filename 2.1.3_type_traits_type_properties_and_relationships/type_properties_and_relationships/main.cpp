// In this exercise, we look at type traits of objects stemming from a simple class hierarchy.
// We use type traits to check if object types have derived/base class relationship, are convertible, is abstract, is polymorphic (true for derived types), etc.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include "util.h"
#include <type_traits>


int main() {
	// All the checks herein evaluates to false except where I put some comments.

	Base base;
	Point point;
	Shape* shape;
	
	std::cout << "\n\nExercise A\n";

	type_properties_a(base);
	type_properties_a(point);  // is polymorphic
	type_properties_a(shape);

	std::cout << "\n\nExercise B\n";

	type_same_class_b<Base, Point>();
	type_same_class_b<Base, Shape>();
	type_same_class_b<Shape, Point>();

	std::cout << "\n\nExercise C\n";

	types_have_gen_spec_relationship_c<Base, Point>();
	types_have_gen_spec_relationship_c<Point, Base>();
	types_have_gen_spec_relationship_c<Base, Shape>();
	types_have_gen_spec_relationship_c<Shape, Base>();
	types_have_gen_spec_relationship_c<Shape, Point>();  // have gen/spec relationship
	types_have_gen_spec_relationship_c<Point, Shape>();

	std::cout << "\n\nExercise D\n";

	types_are_convertible_d<Base, Point>();
	types_are_convertible_d<Base, Shape>();
	types_are_convertible_d<Shape, Point>();

	return 0;
};