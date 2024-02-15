// Simple helper file containing templated free functions for performing variadic manipulations on sets of shapes.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>

using namespace std;


template <typename T, typename ... Ts>
void constexpr rotate(const double& factor, T& t, Ts &... ts)
{
	t.rotate(factor);
	rotate(factor, ts...);
}

template <typename T>
void constexpr rotate(const double& factor, T& t)
{
	t.rotate(factor);
}
