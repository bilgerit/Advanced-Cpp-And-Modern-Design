// In this exercise, we check the machine epsilon for various floating point types using a custom function,
// and later on using the std::numeric_limits<T> class.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <iostream>


template <typename T>
T find_epsilon() {
	T epsilon{ 1. };
	while (((T) 1. + (T) 0.5 * epsilon) != (T)1.0) 
	{
		epsilon *= (T)0.5;
	};
	return epsilon;
}


int ex_a() {
	std::cout << "Exercise a) machine epsilon for different floating point types\n";
	// Given example: double
	double epsilon = 1.0;
	while ((1.0 + 0.5 * epsilon) != 1.0) { epsilon *= 0.5; }
	std::cout << "Epsilon for type double (w/ given example function): " << epsilon << "\n";
	std::cout << "Epsilon for type double: " << find_epsilon<double>() << "\n";
	std::cout << "Epsilon for type float: " << find_epsilon<float>() << "\n";
	std::cout << "Epsilon for type long double: " << find_epsilon<long double>() << "\n";

	return 0;
};

int ex_b() {
	std::cout << "\n\nExercise b) machine epsilons computed with std::numeric_limits<T>\n";
	std::cout << "Epislon for type double: " << std::numeric_limits<double>::epsilon() << "\n";
	std::cout << "Epislon for type float: " << std::numeric_limits<float>::epsilon() << "\n";
	std::cout << "Epislon for type long double: " << std::numeric_limits<long double>::epsilon() << "\n";
	std::cout << "Epislon for type int: " << std::numeric_limits<int>::epsilon() << "\n";
	std::cout << "Epislon for type unsigned int: " << std::numeric_limits<unsigned int>::epsilon() << "\n";
	std::cout << "Epislon for type long: " << std::numeric_limits<long>::epsilon() << "\n";
	std::cout << "Epislon for type unsigned long: " << std::numeric_limits<unsigned long>::epsilon() << "\n";
	return 0;
};

int main() {

	ex_a();
	ex_b();

	return 0;
};