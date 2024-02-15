// In this exercise, we demonstrate the use of function objects in constructors and as member functions, which is useful in modern C++ class design.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include "util.h"


int main()
{
	Shape s(f1);
	Circle c(f1);
	s.rotate(1.0);
	c.rotate(1.0);

	s = Shape(f2);
	c = Circle(f2);
	s.rotate(2.0);
	c.rotate(2.0);

	s = Shape(f3);
	c = Circle(f3);
	s.rotate(3.0);
	c.rotate(3.0);

	return 0;
}