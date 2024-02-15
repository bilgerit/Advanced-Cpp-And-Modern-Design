// Simple helper file containing utility needed for this exercise.
// Chiefly, we define some specific function types, and a bunch of function types: free functions, lambdas, and a functors.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once

#include <iostream>
#include <functional>

#include "util.h"

using namespace std;


// Type definition: Define templated function wrapper type:
// note that this means that the function takes an arg of type const T& and returns type T.
template <typename T>
using FunctionType = std::function<T(const T& t)>;


// Function wrapper type: Evaluate and print a function
template <typename T>
void constexpr print(const FunctionType<T>& f, T t) { std::cout << f(t) << '\n'; }


// Create free funciton
template <typename T>
T constexpr free_function_mulby_2(const T& state)
{
	T multiplier{ 2 };
	return state * multiplier;
};


// Create Function object
template <typename T>
class MultiplierObject
{
private:
	T multiplier;
public:
	MultiplierObject(const T& multiplier) : multiplier(multiplier) {}
	T constexpr operator()(const T& arg) const { return this->multiplier * arg; };
};


// Allow creating Lambda Function
template <typename T>
auto constexpr generate_lambda_multiplier_function(const T& multiplier)
{
	auto lambda_multiplier = [multiplier](const T& arg) -> T
	{
		return multiplier * arg;
	};
	return lambda_multiplier;
};