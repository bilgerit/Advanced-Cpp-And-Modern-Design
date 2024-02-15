// Simple helper file containing a dummy class required for this exercise.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <functional>


class C { 
	// Function object with extra member functions
private: 
	double _data; 
public: 
	C(double data) : _data(data) {}

	double operator () (double factor) 
	{
		return _data + factor; 
	}

	double translate(double factor) 
	{ 
		return _data + factor; 
	}

	double translate2(double factor1, double factor2) 
	{ 
		return _data + factor1 + factor2;
	} 

	static double Square(double x) 
	{ 
		return x * x; 
	}
};
