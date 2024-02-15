// In this exercise, we emulate deprecated C++98 style bind code.
// Specifically, we will create lambda functions that bind to the first or second parameter of a binary function.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <iostream>
#include <functional>
#include <algorithm>

template <typename R, typename D> 
using FunctionType = std::function<R(const D x)>;  // templated function type mapping from type D to type R

using ScalarFunction = FunctionType<double, double>;  // scalar function type mapping from double to double

template <typename T>
std::function<T(const T&)> bind1st(
	const std::function<T(const T& x, const T& y)>& f,
	const T& x_
) {
	// Take a function object requiring 2 arguments and transform it into funciton with 1 argument only by using lambda function.
	// Bind to the first param x of f(x,y)
	return [=](const T& y) { return f(x_, y); };
}

template <typename T>
std::function<T(const T&)> bind2nd(
	const std::function<T(const T& x, const T& y)>& f,
	const T& y_
) {
	// Take a function object requiring 2 arguments and transform it into funciton with 1 argument only by using lambda function.
	// Bind to the second param y of f(x,y)
	return [=](const T& x) { return f(x, y_); };
}

template <typename T>
std::function<T(T, T)> fxy = [] (const T& x, const T& y) -> T { return x * y; };  // templated lambda function object for multiplying two arguments.

int main() {

	double xval = 2.;
	double yval = 10.0; 

	ScalarFunction fx = bind1st<double>(fxy<double>, xval);
	ScalarFunction fy = bind2nd<double>(fxy<double>, yval);
	std::cout << fx(3.0) << std::endl;
	// Test new bind code on vector using STL algorithm std::transform
	std::vector<double> vec(10, 2.0); 

	std::transform(
		vec.begin(), 
		vec.end(), 
		vec.begin(), 
		fx
	); 
	
	for (auto i = 0; i < vec.size(); ++i) 
	{ 
		std::cout << vec[i] << ","; 
	}

	std::cout << std::endl;

	// same as above but using function where 2nd argument got bound.
	std::transform(
		vec.begin(),
		vec.end(),
		vec.begin(),
		fy
	);

	for (auto i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << ",";
	}

	return 0;
};
