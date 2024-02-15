// In this exercise, we demonstrate how using smart pointers can lead to more save code by calling destructors on objects automatically, 
// how to transfer ownership between smart pointers, and how to make code more readable by using alias templates.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <memory>
#include <iostream>
#include <type_traits>

class Point {
	// Dummy class w/ 2 member variables, getters and setters. Will be used for demonstrating how to transfer ownership between smart pointers.
private:
	double _x;
	double _y;
public:
	Point(const double& x, const double& y) : _x(x), _y(y) {};
	double X() { return _x; };
	double Y() { return _y; };
	void X(const double& x) { _x = x; };
	void Y(const double& y) { _y = y; };
};


int ex_a() {
	std::cout << "Exercise a: demonstrating how a memory leak can appear from a sudden exception when working with raw pointers that don't get deallocated properly" << std::endl;
	try { 
		// Block with raw pointer lifecycle
		double* d = new double(1.0);
		Point* pt = new Point(1.0, 2.0); // Two-d Point class
		
		// create memory leak on purpose, since any code below the throw statement will not be executed.
		throw std::runtime_error("Help!");

		// Dereference and call member functions 
		*d = 2.0; 
		(*pt).X(3.0); // Modify x coordinate 
		(*pt).Y(3.0); // Modify y coordinate

		// Can use operators for pointer operations 
		pt->X(3.0); // Modify x coordinate 
		pt->Y(3.0); // Modify y coordinate

		// Explicitly clean up memory (if you have not forgotten) 
		delete d; 
		delete pt; 
	}
	catch (...) {
		std::cout << "Success! We created a memory leak!" << std::endl;
	}
	return 0;
};


int ex_b() {
	std::cout << "\n\nExercise b: demonstrating how to prevent memory leaks caused by sudden exceptions when using smart pointers that deleted the referenced object automatically" << std::endl;

	try {
		// Block with unique ptr
		std::unique_ptr<double> d = std::make_unique<double>(1.0);
		auto pt = std::make_unique<Point>(1., 2.);

		// Throw exception. Any code below this wont be executed. However, default destructors of objects going out of scope (such
		// as the smart pointers) will be called automatically. This prevents a memory leak.
		throw std::runtime_error("Help!");

		// Dereference and call member functions 
		*d = 2.0;
		(*pt).X(3.0); // Modify x coordinate 
		(*pt).Y(3.0); // Modify y coordinate

		// Can use operators for pointer operations 
		pt->X(3.0); // Modify x coordinate 
		pt->Y(3.0); // Modify y coordinate

		// Explicitly clean up memory (if you have not forgotten) 
		d.release();
		pt.release();
	}
	catch (...) {
		std::cout << "Success! No memory leak since the unique ptrs get released automatically when going out of scope!" << std::endl;
	}
	return 0;
};


int ex_c() {
	std::cout << "\n\nExercise c: transferring ownership between pointers." << std::endl;

	int* raw = new int(5);
	std::cout << "Raw pointer " << raw << " w/ value " << *raw << std::endl;

	std::unique_ptr<int> u1(raw);
	std::cout << "Unique pointer " << u1 << " w/ value " << *u1 << " and when applying get(): " << u1.get() << std::endl;

	// Assign 2 unique pointers to the same value: this will break.
	//    std::unique_ptr<int> u2(raw);
	//    std::cout << "New Unique pointer " << u2 << " w/ value " << *u2 << " and when applying get(): " << u2.get() << std::endl;
	//    std::cout << "Old Unique pointer " << u1 << " w/ value " << *u1 << " and when applying get(): " << u1.get() << std::endl;

	// Assign unique pointer to unique pointer: this will break.
	//    auto u2(u1);
	//    std::cout << "New Unique pointer " << u2 << " w/ value " << *u2 << " and when applying get(): " << u2.get() << std::endl;

	// Transferring ownership from one pointer to another
	std::unique_ptr<int> u2(std::move(u1));
	std::cout << "New Unique pointer " << u2 << " w/ value " << *u2 << " and when applying get(): " << u2.get() << std::endl;
	std::cout << "Old Unique pointer " << u1 << ". Is it a nullpointer now: " << (u1 == nullptr) << std::endl;

	return 0;
};

// alias template for unique ptr
template <typename T>
using uptr = std::unique_ptr<T>;

// regular alias
using puptr = std::unique_ptr<Point>;


void ex_d() {
	std::cout << "\n\nExercise d: demonstrating alias templates." << std::endl;

	uptr<int> p1 = std::make_unique<int>(1.);
	puptr p2 = std::make_unique<Point>(1., 2.);
}

int main() {

	ex_a();
	ex_b();
	ex_c();
	ex_d();

	return 0;
};