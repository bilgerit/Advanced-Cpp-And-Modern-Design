// Simple helper file containing utility needed for this exercise.
// Specifically, we define various operators and functions operating on functions (hence creating higher order functions).
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <iostream>
#include <functional>
#include <cmath>

// Function types mapping Domain D to Range R (templated function type)
template <typename R, typename D>
using FunctionType = std::function<R(const D x)>;    // D -> R
// Working function type: use templated function type to create function that maps from double to double
using ScalarFunction = FunctionType<double, double>;  

template <typename R, typename D>
FunctionType<R, D> operator + (const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	// Addition of functions via operator overloading; D->R; yields a new function.
	// [=] used to make copies of f and g, ensuring that the lambda function is not dependent on the original f and g.
	// Takes 2 function objects and creates a new function object.
	return [=](const D& x) {
		return f(x) + g(x);
		};
}

template <typename R, typename D>
FunctionType<R, D> operator * (const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	// Multiplication of functions; D->R; yields a new function.
	return [=](const D& x) {
		return f(x) * g(x);
		};
}

template <typename R, typename D>
FunctionType<R, D> operator / (const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	// Multiplication of functions; D->R; yields a new function.
	return [=](const D& x) {
		return f(x) / g(x);
		};
}

template <typename R, typename D>
FunctionType<R, D> operator - (const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	// Subtraction of functions; D->R; yields a new function.
	return [=](const D& x) {
		return f(x) - g(x);
		};
}

template <typename R, typename D>
FunctionType<R, D> operator - (const FunctionType<R, D>& f) {
	// Unary additive inverse; D->R; yields a new function.
	return [=](const D& x) {
		return -f(x);
		};
}

template <typename R, typename D>
FunctionType<R, D> operator * (const R& r, const FunctionType<R, D>& f) {
	// scalar multiplication; D->R; yields a new function.
	return [=](const D& x) {
		return r * f(x);
		};
}

template <typename R, typename D>
FunctionType<R, D> operator << (const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	// Function composition; D->R; yields a new function.
	return [=](const D& x) {
		return f(g(x));
		};
}

template <typename R, typename D>
FunctionType<R, D> exp(const FunctionType<R, D>& f) {
	// The exponential function; yields a new function.
	return [=](const D& x) { return std::exp(f(x)); };
}

template <typename R, typename D>
FunctionType<R, D> cos(const FunctionType<R, D>& f) {
	// The exponential function; yields a new function.
	return [=](const D& x) { return std::cos(f(x)); };
}

template <typename R, typename D>
FunctionType<R, D> sin(const FunctionType<R, D>& f) {
	// The exponential function; yields a new function.
	return [=](const D& x) { return std::sin(f(x)); };
}

template <typename R, typename D>
FunctionType<R, D> tan(const FunctionType<R, D>& f) {
	// The exponential function; yields a new function.
	return [=](const D& x) { return std::tan(f(x)); };
}

template <typename R, typename D>
FunctionType<R, D> log(const FunctionType<R, D>& f) {
	// The exponential function; yields a new function.
	return [=](const D& x) { return std::log(f(x)); };
}

template <typename R, typename D>
FunctionType<R, D> abs(const FunctionType<R, D>& f) {
	// The exponential function; yields a new function.
	return [=](const D& x) { return std::abs(f(x)); };
}

template <typename R, typename D>
FunctionType<R, D> sqrt(const FunctionType<R, D>& f) {
	// The exponential function; yields a new function.
	return [=](const D& x) { return std::sqrt(f(x)); };
}

template <typename R, typename D>
FunctionType<R, D> min(const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	// The exponential function; yields a new function.
	return [=](const D& x) { return std::min(f(x), g(x)); };
}

template <typename R, typename D>
FunctionType<R, D> max(const FunctionType<R, D>& f, const FunctionType<R, D>& g) {
	// The exponential function; yields a new function.
	return [=](const D& x) { return std::max(f(x), g(x)); };
}
