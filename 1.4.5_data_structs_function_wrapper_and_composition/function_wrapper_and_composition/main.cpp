// In this exercise, we have another look at using funciton objects to create flexible software.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include "util.h"


int main()
{
	// Next gen stuff
	auto square = [](double d) 
	{
		return d * d; 
	}; 
	auto expo = [](double d) 
	{
		return std::exp(d); 
	}; 
	NextGenPolymorphism<double> ng(square, 1.0); 
	std::cout << "Square: " << ng.execute(2.0) << std::endl; // 4 
	// square is not cool, switch to expo 
	ng.switchFunction(expo); 
	std::cout << "Exponential: " << ng.execute(5.0) << std::endl; // 148.413


	// a, b
	int state{ 2 };

	FunctionType<int> f = cube_rotation<int>;
	Shape s(state, f);
	s.rotate();

	FunctionType<int> g = square_rotation<int>;
	s.switch_rotation_func(g);
	s.rotate();

	FunctionType<int> h = LineRotation<int>();
	s.switch_rotation_func(h);
	s.rotate();

	return 0;
}
