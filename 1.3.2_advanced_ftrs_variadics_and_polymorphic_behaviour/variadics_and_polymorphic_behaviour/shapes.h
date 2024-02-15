// Simple helper file containing a bunch of simple classes w/ simple hierarchy.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>


class Shape { 
public: 
	virtual void rotate(double d) = 0; 
};


class Circle : public Shape { 
public: 
	void rotate(double d) override { std::cout << "c\n"; } 
};


class Line : public Shape {
public:
	void rotate(double d) override { std::cout << "l\n"; }
};


class Valve { 
public: 
	void rotate(double d) { std::cout << "v\n"; }
};

