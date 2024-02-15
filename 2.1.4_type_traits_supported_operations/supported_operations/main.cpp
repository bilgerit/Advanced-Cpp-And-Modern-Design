// In this exercise, we look at various advanced type traits of classes / objects.
// Examples: has virtual destructor, has default constructor, has copy constructor, has move constructor, is copy assignable, is move assignable.
// We then check how these are by default present in some classes, and how they can be removed via the delete keyword.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <type_traits>
#include <iostream>

class Shape {
	// abstract base class
public:
	virtual void draw() = 0;
};

class Point : public Shape {
	// abstrated derived class
public:
	Point() {}
	virtual void draw() override {}
};

class PointD : public Shape {
	// abstrated derived class
public:
	PointD() {}
	virtual void draw() override {}
	PointD(const PointD&) = delete;
	PointD(PointD&&) = delete;
};

class PointE : public Shape {
	// abstrated derived class
public:
	PointE() {}
	virtual void draw() override {}
	PointE(const PointE&) {};
	PointE(PointE&&) {};
};

template <typename T>
void checks() {
	// Function that performs the checks asked for in the exercise. Print the results to console.

	// check if has virtual destructor
	std::cout << "Has virtual destructor: " << std::has_virtual_destructor_v<T> << std::endl;

	// check if has constructors: default, copy, move
	std::cout << "Has default constructor: " << std::is_default_constructible_v<T> << std::endl;
	std::cout << "Has copy constructor: " << std::is_copy_constructible_v<T> << std::endl;
	std::cout << "Has move constructor: " << std::is_move_constructible_v<T> << std::endl;

	// check if is assignable: copy, move
	std::cout << "Is copy assignable: " << std::is_copy_assignable_v<T> << std::endl;
	std::cout << "Is move assignable: " << std::is_move_assignable_v<T> << std::endl;
}

int main() {
	std::cout << "Exercises a to c: " << std::endl;
	// default, copy and move constructors are implicitly defined for Point. Same for move and copy assignment.
	checks<Point>();
	std::cout << std::endl;

	std::cout << "Exercise d: " << std::endl;
	// copy and move constructors are now removed in PointD
	checks<PointD>();

	std::cout << std::endl;
	std::cout << "Exercise e: " << std::endl;
	// default, copy and move constructors are implicitly defined in point E.
	// unlike in a, however, the copy and move assignments are not implicitly defined anymore.
	checks<PointE>();

	return 0;
};