// In this exercise, we combine usage of function wrappers with class member functions and objects.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include "util.h"
using namespace std;


int main()
{
	double num{ 2. };

	// a
	// use C:: as we bind to a static member function.
	auto Square = std::bind(&C::Square, placeholders::_1);

	// b
	// need to use C-> and pass object to bind to non-static member function.
	// the resulting bounded function will be bound to a specific instance.
	C c(num);
	auto translate1 = std::bind(&C::translate, &c, placeholders::_1);
	auto translate2 = std::bind(&C::translate2, &c, placeholders::_1, placeholders::_2);

	// c
	// call the functiond and test the results.
	auto res1 = translate1(1.);
	auto res2 = translate2(1., 1.);

	cout << "Number: " << num << endl;
	cout << "Square: " << Square(num) << endl;
	cout << "Translate1: " << res1 << endl;
	cout << "Translate2: " << res2 << endl;
	return 0;
}
