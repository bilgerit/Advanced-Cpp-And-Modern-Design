// In this exercise, we compute statistics on containers.
// The tools work both wih STL containers (vectors, etc.) as well as with uBLAS vectors (the latter requires implementing the logic using indexing rather than pointers).
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include "util.h"
#include <iostream>

int ex_a_b_c()
{
	STLVector<double> v{ 1, 2, 2, 3 };
	auto [mean, mean_deviation, range, standard_deviation, variance] = calc_summary_stats<STLVector<double>, double>(v);
	auto median = calc_median_of_sorted_container<STLVector<double>, double>(v);
	auto mode = calc_mode<STLVector<double>, double>(v);
	std::cout << "STL Vector: mean: " << mean << ", mean deviation: " << mean_deviation << ", range: " << range << ", standard deviation: " << standard_deviation << 
		", variance: " << variance << ", median: " << median << ", mode: " << mode <<  std::endl;

	UBLASVector<double> b(4, 0);  // 3 elements, initialized to 0
	b[0] = 1;
	b[1] = 2;
	b[2] = 2;
	b[3] = 3;
	auto [mean_b, mean_deviation_b, range_b, standard_deviation_b, variance_b] = calc_summary_stats<UBLASVector<double>, double>(b);
	auto median_b = calc_median_of_sorted_container<UBLASVector<double>, double>(b);
	auto mode_b = calc_mode<UBLASVector<double>, double>(b);
	std::cout << "UBLAS Vector: mean: " << mean_b << ", mean deviation: " << mean_deviation_b << ", range: " << range_b << ", standard deviation: " << standard_deviation_b <<
		", variance: " << variance_b << ", median: " << median_b << ", mode: " << mode_b << std::endl;

	return 0;
}



int main()
{
	ex_a_b_c();
	return 0;
}
