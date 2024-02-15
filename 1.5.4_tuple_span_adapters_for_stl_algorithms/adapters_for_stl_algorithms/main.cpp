// In this exercise, we learn to use 'adapters' to overcome interface missmatches between STL algorithms and containers.
// Specifically, we will have to map container pointers to indices and vice versa.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include "util.h"


void ex_a() {
	std::vector<double> v{ 1, 2, 3, 4, 5, 6 };
	double target_value{ 3.1 };

	int idx = ex_a_find_idx_of_first_element(v, target_value);
	std::cout << "Exercise a: The index of the first element in the vector " << container_to_string<std::vector<double>>(v) 
		<< " for which vec[i] <= x < vec[i] for x = " << target_value << " is " << idx << std::endl;
}


void ex_b() {
	using Vec = std::vector<double>;

	Vec x{ 1, 2, 3, 4, 5 };
	Vec y{ 2, 1, 2, 2.5, 4 };
	int i{ 1 };
	int j{ 4 };
	std::string ABSOLUTE_ERROR{ "ABSOLUTE_ERROR" };
	std::string RELATIVE_ERROR{ "RELATIVE_ERROR" };

	FindMaxErrorInRange<Vec, Vec::value_type> fabs(ABSOLUTE_ERROR);
	FindMaxErrorInRange<Vec, Vec::value_type> frel(RELATIVE_ERROR);

	std::cout << "Exercise b: vector x: " << container_to_string<Vec>(x) << ", vector y: " << container_to_string<Vec>(y) << "." << std::endl;
	std::cout << "We're computing the errors between indices (" << i << ", " << j << ") of the two vectors." << std::endl;
	
	auto [abs_error, abs_error_idx] = fabs(x, y, i, j);
	auto [rel_error, rel_error_idx] = frel(x, y, i, j);

	std::cout << "The maximum absolute error is " << abs_error << " at index " << abs_error_idx << std::endl;
	std::cout << "The maximum relative error is " << rel_error << " at index " << rel_error_idx << std::endl;
}


int main() {
	ex_a();
	ex_b();
	return 0;
}