// Simple helper file containing utility needed for this exercise.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <functional>

double freeFunction3(double x, double y, double z) 
{ 
	// Add up three elements
	return x + y + z; 
}

/* Note: what we do in the following effectively does the same as a naive wrapper one might find for example in Python:

double freeFunction2(double x, double y) {
	return freeFunction3(x, y, 0.);
};

*/

// Partial evaluation example: Sum on 0, 1, or 2 elements instead of 3.
auto freeFunction2 = std::bind(freeFunction3, 0., std::placeholders::_1, std::placeholders::_2);
auto freeFunction1 = std::bind(freeFunction3, 0., 0., std::placeholders::_1);
auto freeFunction0 = std::bind(freeFunction3, 0., 0., 0.);
