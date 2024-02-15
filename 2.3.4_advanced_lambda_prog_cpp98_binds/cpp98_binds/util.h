#pragma once
#include <iostream>
#include <functional>

template <typename T> 
std::function<T(const T&)> bind1st(
	const std::function<T(const T& x, const T& y)>& f, 
	const T& x_
) { 
	// Bind to the first param x of f(x,y)
	return [=](const T& y) { return f(x_, y); };
}

template <typename T> 
std::function<T(const T&)> bind2nd(
	const std::function<T(const T& x, const T& y)>& f, 
	const T& y_
) { 
	// Bind to the second param y of f(x,y)
	return [=](const T& x) { return f(x, y_); };
}


