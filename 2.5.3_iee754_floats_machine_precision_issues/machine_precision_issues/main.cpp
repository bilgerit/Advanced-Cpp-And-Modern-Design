// In this exercise, explore numerical precision limits and operations around them for doubles using boost/math/special_functions/next.hpp.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <iostream>
#include <boost/math/special_functions/next.hpp>


int main() {

	// Precision when printing to console (default = 6, max = 19):
	int prec{ 19 };

	// ---------------
	// Given code (w/ some comments added):
	
	// Number gaps/bits/ULP between 2 floating-point values a and b 
	// Returns a signed value indicating whether a < b 

	double a = 0.1; 
	double b = a + std::numeric_limits<double>::min();  // std::numeric_limits<double>::min() == 2.22507e-308
	std::cout << "float_distance((double) 0.1, (double) 0.1 + std::numeric_limits<double>::min()): " << std::setprecision(prec) << boost::math::float_distance(a, b) << std::endl;  // 0

	a = 1.0; 
	b = 0.0; 
	std::cout << "float_distance((double) 1.0, (double) 0.0): " << std::setprecision(prec) << boost::math::float_distance(a, b) << std::endl;  // -4607182418800017408

	// ---------------

	// float_next
	// The next representable value that is greater than x. An overflow_error is thrown if no such value exists (
	std::cout << std::setprecision(prec) << boost::math::float_next((double) 1.0) << std::endl;  // 1.000000000000000222

	// float_prior
	// The next representable value that is less than x. An overflow_error is thrown if no such value exists
	std::cout << std::setprecision(prec) << boost::math::float_prior((double) 1.0) << std::endl;  // 0.999999999999999889

	// fload_advance
	// Advance a floating-point number by a specified number of ULP (Unit in Last Place)
	std::cout << std::setprecision(prec) << boost::math::float_advance((double) 1.0, 1) << std::endl;  // 1.000000000000000222
	std::cout << std::setprecision(prec) << boost::math::float_advance((double)1.0, 2) << std::endl;  // 1.000000000000000444
	std::cout << std::setprecision(prec) << boost::math::float_advance((double)1.0, 10) << std::endl;  // 1.00000000000000222

	// float_distance
	// Find the number of gaps/bits/ULP between two floating-point value
	std::cout << std::setprecision(prec) << boost::math::float_distance(boost::math::float_next((double)1.0), boost::math::float_prior((double)1.0)) << std::endl; // -2

	// nextafter
	// Return the next representable value of x in the direction y
	std::cout << std::setprecision(prec) << boost::math::nextafter((double) 1.0, (double) 2.0) << std::endl;  // 1.000000000000000222 (same as moving 1 ULP, see above)

	return 0;
};