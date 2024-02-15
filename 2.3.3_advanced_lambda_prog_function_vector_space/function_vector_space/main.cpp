// In this exercise, we take a look at higher order functions for arithmetic operations.
// Specifically, we create custom function types, and define overloaded operators to combine custom functions to new functions.
// We also explore how we can combine these custom function objects with the standard library algorithms and cmath functions.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include "util.h"

int ex_a() {
	std::cout << "Exercise a: creating higher order functions for aritmhetic operations on scalars." << std::endl;

	// Scalar functions: double to double
	ScalarFunction f = [](double x) {return x * x; };
	ScalarFunction g = [=](double x) { return x; };
	std::cout << g(2) << ", " << g(8) << "*";

	// Set I: Arithmetic functions
	double scale = 2.0;
	auto fA = 2.0 * (f + g);
	auto fM = f - g;
	auto fD = f / g;
	auto fMul = f * g;
	auto fC = g << g << 4.0 * g; // Compose: g(g(4*g(_)))
	auto fMinus = -(f + g);
	
	double x = 5.0;
	std::cout << fA(x) << ", " << fM(x) << ", " << fD(x) << ", " << fMul(x) << ", compose: " << fC(x) << ", " << fMinus(x) << std::endl;

	return 0;
};

int ex_b() {
	std::cout << "\nExercise b: creating more higher order functions wrapping around cmath functions." << std::endl;

	ScalarFunction f = [](double x) {return x * x; };
	ScalarFunction g = [=](double x) { return x; };

	auto ftmp = log(g); 
	auto ftmp2 = cos(f); 
	auto f2 = (abs(exp(g)) * log(g) + sqrt(ftmp)) / ftmp2; 
	
	double x = 5.0;
	std::cout << f2(x) << std::endl;

	return 0;
};

int ex_c() {
	std::cout << "\nExercise b: creating more higher order functions wrapping around algorithm functions." << std::endl;

	ScalarFunction f = [](double x) {return x * x; };
	ScalarFunction g = [=](double x) { return x; };

	auto h1 = min(f, g); 
	auto h2 = max(f, g); 
	std::cout << "min(f,g): " << h1(2.0) << '\n'; 
	std::cout << "max(f,g): " << h2(2.0) << '\n';
	return 0;
};

int main() {
	ex_a();
	ex_b();
	ex_c();

	return 0;
};