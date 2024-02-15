// In this exercise, we take a look at floating point classification / type traits.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <iostream>
#include <cmath>

template <typename T>
const char* Classify(T t) {
	// Floating Point Classification
	switch (std::fpclassify(t))
	{
	case FP_INFINITE: return "Inf";
	case FP_NAN: return "NaN";
	case FP_NORMAL: return "normal";
	case FP_SUBNORMAL: return "subnormal";
	case FP_ZERO: return "zero";
	default: return "unknown";
	}
}

template <typename T>
void PrintClassifyB(T t) {
	// Variable classification: is finite / infinite / nan / normal.
	std::cout << "Variable " << t << " of type " << typeid(t).name() << ":\n"
		<< std::boolalpha
		<< "is finite: " << std::isfinite(t)
		<< "; is infinite: " << std::isinf(t)
		<< "; is nan: " << std::isnan(t)
		<< "; is normal: " << std::isnormal(t)
		<< std::endl;
}


int ex_a() {
	std::cout << "Exercise A\n";
	double val = std::numeric_limits<double>::max();
	double val2 = std::numeric_limits<double>::min() - 3.1415;
	std::cout
		<< Classify(val) << ", "                // normal
		<< Classify(2.0 * val) << ", "          // inf
		<< Classify(3.1415 + val) << ", "       // normal
		<< Classify(val2) << ", "               // normal
		<< Classify(val2 / 2.0) << ", "         // normal
		<< Classify(DBL_MIN / 2.) << std::endl; // subnormal
	return 0;
};

int ex_b() {
	std::cout << "\nExercise B\n";

	double factor = 2.0; 
	auto val = factor*std::numeric_limits<double>::max();
	
	PrintClassifyB(factor);  // finite, normal
	PrintClassifyB(val);  // inf
	PrintClassifyB(val - val);  // nan
	PrintClassifyB(std::sqrt(-1.0));  // nan
	PrintClassifyB(std::log(0.0));  // inf
	PrintClassifyB(std::exp(val));  // inf

	return 0;
};

int main() {

	ex_a();
	ex_b();

	return 0;
};