// In this exercise, we explore the deprecated auto_ptr.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <memory>
#include <iostream>

int ex_a() {
	// Exception is thrown when the second auto_ptr is created and d is undefined.

	/*
	using std::auto_ptr;

	// Define auto_ptr pointers instead of raw pointers 
	std::auto_ptr <double> d(new double(1.0));

	// Dereference 
	*d = 2.0;

	// Change ownership of auto_ptr 
	// (after assignment, d is undefined) 
	auto_ptr <double> d2 = d; 
	*d2 = 3.0;
	std::cout << "Auto values: " << *d.get() << ", " << *d2.get();
	*/
	return 0;
};


int ex_b() {
	// Define unique_ptr pointers instead of raw pointers 
	std::unique_ptr <double> d = std::make_unique<double>(1.);

	// Dereference 
	*d = 2.0;

	// Assignment is not possible, since there can only be a unique owner 
	// std::unique_ptr <double> d2 = d;	

	// Create via dereferencing
	std::unique_ptr<double> d2 = std::make_unique<double>(*d);
	// OR: Create via move
	std::unique_ptr<double> d3(std::move(d));

	*d2 = 3.14;

	std::cout << "d is now nullptr: " << std::boolalpha << (d == nullptr) << std::endl;
	std::cout << "unique_ptr values: *d2.get()=" << *(d2.get()) << "; *d3.get()=" << *(d3.get()); 

	return 0;
};


int main() {

	ex_a();
	ex_b();

	return 0;
};