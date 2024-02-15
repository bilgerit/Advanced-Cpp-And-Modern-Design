// In this exercise, we explore the Builder pattern.
// Simply speaking, the builder pattern is a way to build up a set of related objects in a congruent manner.
// Here, the builders tie together IODevice and Shape subtypes (IODeviceA, IODevice B, and Circle, Line).
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <vector>
#include "Builders.h"

int main() {
	CircleBuilderA circle_builder_a;
	CircleBuilderB circle_builder_b;
	LineBuilderA line_builder_a;
	LineBuilderB line_builder_b;

	auto [ShapePointerA, IODevicePointerA] = circle_builder_a.getProduct();
	ShapePointerA->display(*IODevicePointerA);

	auto [ShapePointerB, IODevicePointerB] = circle_builder_b.getProduct();
	ShapePointerB->display(*IODevicePointerB);

	auto [ShapePointerC, IODevicePointerC] = line_builder_a.getProduct();
	ShapePointerC->display(*IODevicePointerC);

	auto [ShapePointerD, IODevicePointerD] = line_builder_b.getProduct();
	ShapePointerD->display(*IODevicePointerD);

	return 0;
}
