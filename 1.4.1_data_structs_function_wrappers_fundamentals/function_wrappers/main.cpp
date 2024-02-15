// In this exercise, we demonstrate the usage of function wrappers with various function objects.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include "util.h"


int main()
{
	double state{ 1. };
	double multiplier{ 2. };

	FunctionType<double> f;

	f = free_function_mulby_2<double>;
	print(f, state);

	state += 1;
	f = MultiplierObject<double>(multiplier);
	print(f, state);

	state += 1;
	f = generate_lambda_multiplier_function<double>(multiplier);
	print(f, state);

	return 0;
};