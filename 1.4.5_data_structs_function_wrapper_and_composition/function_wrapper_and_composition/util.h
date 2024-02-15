// Simple helper file containing utility needed for this exercise.
// Specifically, we are showing how to use function objects as member variables to create flexible software designs.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <functional>
#include <iostream>

template <typename T>
using FunctionType = std::function<T(const T& t)>;  // function type w/ single argument and equal return type.

template <typename T>
class NextGenPolymorphism
{
private:
	FunctionType<T> _func;
	T _fac;
public:
	NextGenPolymorphism(const FunctionType<T>& function, const T& factor) : _fac(factor)
	{
		_func = function;
	}

	T execute(double d)
	{
		return _func(d) * _fac;
	}

	void switchFunction(const FunctionType<T>& function)
	{
		_func = function;
	}
};

template <typename T>
class Shape
{
private:
	T _state;
	FunctionType<T> _rotation_func;
public:
	Shape(T& state, FunctionType<T>& rotation_func) : _state(state), _rotation_func(rotation_func) {};
	T rotate() {
		std::cout << "Rotation called: ";
		_rotation_func(_state);
		return _state;
	};
	void switch_rotation_func(const FunctionType<T>& function)
	{
		_rotation_func = function;
	};
	T getState() { return _state; };
};

template <typename T>
FunctionType<T> cube_rotation = [](const T& state) {
	std::cout << "Cube rotated" << std::endl;
	return state;
};

template <typename T>
T square_rotation(const T& state)
{
	std::cout << "Square rotated" << std::endl;
	return state;
};

template <typename T>
class LineRotation
{
public:
	LineRotation() = default;
	T operator ()(const T& state)
	{
		std::cout << "Line rotated" << std::endl;
		return state;
	}
};
