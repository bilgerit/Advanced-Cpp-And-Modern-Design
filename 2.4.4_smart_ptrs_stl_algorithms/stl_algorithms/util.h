// Simple helper file containing utility needed for this exercise.
// Specifically, we define a simple class hierarchy, and a simple factory function to the derived class yielding shared pointers.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <iostream>
#include <memory>

class Base { 
	// Base class w/ virtual destructor.
private: 
public: 
	Base() { } 
	virtual void print() const = 0;
protected: 
	virtual ~Base() { std::cout << "Base destructor\n\n"; }
};

class Derived : public Base { 
	// Derived class private:
public: 
	Derived() : Base() { } 
	~Derived() { std::cout << "Derived destructor\n"; } 
	void print() const { std::cout << "derived object\n"; }
};

std::shared_ptr<Derived> factory_shared_derived() {
	// factory to create shared pointers to default initialized Derived type objects.
	return std::make_shared<Derived>();
}
