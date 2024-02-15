// Simple helper file containing utility needed for this exercise.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>

using namespace std;


/* Print functions implemented via function overloading */

// Termination function (i.e., function accepting a single input only)
template <typename T>
void constexpr print(const T& arg) {
	cout << arg << endl;
}

// Variadic function:
// note: '...' denotes a parameter pack
// This function keeps on calling itself until the terminal call,
// where it simply calls the terminal function (see above).
template <typename T, typename... Types>
void constexpr print(const T& arg, const Types& ... args) {
	cout << arg << " ";
	print(args...);
}
