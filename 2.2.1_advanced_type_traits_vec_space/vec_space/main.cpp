// In this exercise, we use bridge functions to perform arithmetic operations on scalars and compounds (vectors, arrays, complex numbers), and then print the results.
// The added flexilibity allows handling of both scalar quantities and compounds, as well as complex types.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include "util.h"
#include <vector>
#include <array>
#include <complex>


int ex_a_b_c_d() {
	std::cout << "Exercise a/b/c/d\n" << std::endl;

	double a{ 1 };
	double b{ 2 };
	std::vector<double> v{ 1, 2, 3, };
	std::vector<double> w{ 2, 3, 4, };
	std::array<double, 3> x{ 1, 2, 3, };
	std::array<double, 3> y{ 2, 3, 4, };  // arrays require us to not use push_back.

	Print(Addition(a, b));
	Print(Addition(v, w));
	Print(Addition(x, y));
	Print(AdditiveInverse(a));
	Print(AdditiveInverse(v));
	Print(AdditiveInverse(x));
	Print(ScalarMultiplication(b, v));
	Print(ScalarMultiplication(b, x));
	return 0;
};


int ex_e() {
	// Complex is a compound! 
	// However, unlike other compounts, Complex types do not posses a .size() method. 
	// 
	// This forced me to rewrite some code (see util.h file), such that the code became less flexible, since now it can't handle containers of containers.
	// We could have instead expanded the bridge functions to include complex types, so that sub-functions take two true_type / false_type arguments,
	// with the second argument specifying whether something is complex or not.
	// But this level of flexibility was not part of the exercise, and I omit it herein.
	std::cout << "\n\n\nExercise e\n" << std::endl;
	double i{ 2 };
	std::complex<double> a{ 1, 2 };
	std::vector<std::complex<double>> c = { {1,2}, {3,4}, {5,6} };
	std::vector<std::complex<double>> d = { {1,2}, {3,4}, {5,6} };

	Print(Addition(c, d));
	Print(AdditiveInverse(c));
	Print(ScalarMultiplication(i, c));
	Print(ScalarMultiplication(a, c));

	return 0;
};


int main() {

	ex_a_b_c_d();
	ex_e();

	return 0;
};