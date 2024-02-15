// Simple helper file containing utility needed for this exercise.
// We took the original implementation and added various fixed to it (see list below).
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>

// FIXES:
// 1) Derived can't be final if we want to inherit it. Add keyword final to Derived2 instead.
// 2) Base class destructor should be virtual such that we can use pointers of base class type (this makes sure that the derived objects destructor is called too).
// 3) Added a <draw> function with <const> keyword to the base class s.t. it can be overridden in the derived class.
// 4) Make base class function <print> virtual such that it can be overriden in the base class.

struct Base { 
	// Interface
	virtual void draw() { 
		std::cout << "print a base\n"; 
	} 
	virtual void draw() const {
		std::cout << "print a base\n";
	}
	virtual void print() {} 
	virtual ~Base() { 
		std::cout << "bye base\n"; 
	} 
};

struct Derived : public Base { 
	// Base subtype Derived.
	Derived() {} 
	void draw() override { 
		std::cout << "print a derived\n"; 
	} 
	void draw() const override {} 
	void print() override {} 
	~Derived() { 
		std::cout << "bye derived\n"; 
	} 
};

class Derived2 final : public Derived {
	// Derived subtype Derived2.
};