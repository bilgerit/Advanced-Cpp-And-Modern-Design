// In this exercise, we use variadic functions and base class pointers to manipulate some custom objects.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once

#include <iostream>
#include <array>

#include "shapes.h"
#include "util.h"

using namespace std;


int main() 
{
	// a, b
	Circle circle;
	Line line;
	Valve valve;
	double factor = 2.0;

	rotate(factor, circle);
	rotate(factor, circle, line); 
	rotate(factor, circle, valve); 
	rotate(factor * 2, circle, valve, line);

	// c
	// We can't include Valve in the array as we have an array of Shape pointers.
	// Valve is not derived from Shape, unlike the other objects.
	// However, Valve can be included in the variadic approach, as the variadic approach is templated without referece to a 
	// specific type of class such as Shape.
	std::array<Shape*, 5> shapeList{ &circle, & line, & circle, & circle, & line };
	double factor2 = 20.0;
	for (auto& elem : shapeList) { elem->rotate(factor2); }

	return 0;
};
