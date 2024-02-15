// Simple helper file containing utility needed for this exercise.
// Importantly, we demonstrate using function objects in a constructor.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <functional>

using VoidFunctionType = std::function<void(double)>;


class Shape { 
protected:
	VoidFunctionType f;
public: 
	// virtual void rotate(double d) { this->f(d) };
	void rotate(double d) { this->f(d); };
	Shape(const VoidFunctionType &f) : f(f) {};

};
					

class Circle : public Shape {
public:
	Circle(const VoidFunctionType& f) : Shape(f) {};
	void rotate(double d) 
	{ 
		// simple wrapper around the base class rotate member function.
		std::cout << "c\n"; 
		Shape::rotate(d);
	}
					
};


// Void Function Examples
VoidFunctionType f1 = [](double d) -> void { std::cout << "f: Lambda Void Function " << d << std::endl; };

class FunctionObject{
	public:
	void operator()(double d) { std::cout << "f: Functor Void Function " << d << std::endl; };
};
VoidFunctionType f2 = FunctionObject();

void f3(double d) { std::cout << "f: Free Function " << d << std::endl; }
