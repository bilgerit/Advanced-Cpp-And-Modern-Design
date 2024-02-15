// In this exercise, we look at smart pointer and their use count upon changes in scope, as well as
// assignment, move, swap, copy, and reinitialization operations.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <memory>
#include <iostream>

class C1 {
	// dummy class -- mostly we want to see the destructor printing a message upon destruction.
private:
	//double* d; OLD WAY 
	std::shared_ptr<double> d;
public:
	C1(std::shared_ptr<double> value) : d(value) {}  // constructor accepting shared ptr -- makes the member variable a pointer to a shared resource.
	virtual ~C1()
	{
		std::cout << "\nC1 destructor\n";
	}
	void print() const {
		std::cout << "Value " << *d;
	}
};

class C2 {
	// dummy class; same as C1 but the destructor will print different text to console.
private:
	//double* d; OLD WAY 
	std::shared_ptr<double> d;
public:
	C2(std::shared_ptr<double> value) : d(value) {}
	virtual ~C2()
	{
		std::cout << "\nC2 destructor\n";
	}
	void print() const {
		std::cout << "Value " << *d;
	}
};

class Point {
	// dummy Point class
private:
	double _x;
	double _y;
	std::shared_ptr<Point> _p;
public:
	Point() = default;
	Point(const double& x, const double& y) : _x(x), _y(y) {}
	explicit Point(const std::shared_ptr<Point>& p) {
		_p = p;
		_x = (*p).X();
		_y = (*p).Y();
	}
	double X() {
		return _x;
	}
	double Y() {
		return _y;
	}
};


int ex_b() {
	std::cout << "\nExercise b: Checking owner counts and destructor calls when changing scopes.\n";
	// Note that the use_count will go to zero only after we exit ex_b, unless we call reset, which isn't needed in practical applications since 
    // smart pointers handle memory releasing themselves upon going out of scope.

	std::shared_ptr<double> d = std::make_shared<double>(3.14);

	std::cout << "owner count of before d: " << d.use_count() << std::endl;
	
	{
		// New scope: create new C1 class. Owner count of shared ptr will increase, and then decrease when we go out of this scope.
		C1 c1(d);
		std::cout << "owner count of d within scope: " << d.use_count() << std::endl;
		{
			// Another new scope. Same effect as above.
			C2 c2(d);
			std::cout << "owner count of d within second scope: " << d.use_count() << std::endl;
		}
		std::cout << "owner count of d after 2nd scope: " << d.use_count() << std::endl;

	}
	std::cout << "owner count of d after both scopes: " << d.use_count() /* 1 */ << std::endl;

	d.reset();  // release the resource.
	std::cout << "owner count of d after calling reset: " << d.use_count() /* 0 */ << std::endl;
	return 0;
};


int ex_c() {

	std::cout << "\nExercise c: same as b but using user defined Point class.\n";

	std::shared_ptr<Point> d = std::make_shared<Point>(3.14, 2.7);

	std::cout << "initial owner count: " << d.use_count() << std::endl;

	{
		std::shared_ptr<Point> d1 = d;
		std::cout << "owner count after creating 2nd shared ptr d1: " << d.use_count() << std::endl;
		{
			Point p(d);
			std::cout << "owner count after constructing p: " << d.use_count() << std::endl;
		}
		std::cout << "owner count of after p went out of scope: " << d.use_count() << std::endl;

	}
	std::cout << "owner count of d1 also went out of scope: " << d.use_count() /* 1 */  << std::endl;

	return 0;
};

int ex_d() {
	std::cout << "\nExercise d: checking object values, addresses and use counts when using smart pointers w/ assigmenent, copy, move, swap, and reinitialization.\n";

	auto p1 = std::make_shared<double>(3.14);
	std::cout << "p1: " << p1 << ", *p1: " << *p1 << ", p1.get(): " << p1.get() << ", p1.use_count(): " << p1.use_count() /* 1 */ << std::endl;

	// Assignment
	std::cout << "assignment:" << std::endl;
	auto p2 = p1;
	std::cout << "p2: " << p2 << ", *p2: " << *p2 << ", p2.get(): " << p2.get() << ", p2.use_count(): " << p2.use_count() /* 2 */ << std::endl;

	// Copy (copies the underlying value, and hence doesn't point to the same resouce)
	std::cout << "copy:" << std::endl;
	auto p3 = std::make_shared<double>(*p1);
	std::cout << "p3: " << p3 << ", *p3: " << *p3 << ", p3.get(): " << p3.get() << ", p3.use_count(): " << p3.use_count() /* 1 */ << std::endl;

	// Move (ownership is moved, hence use count stays the same)
	std::cout << "move:" << std::endl;
	auto p4 = std::move(p1);
	std::cout << "p1: " << p1 << std::endl;  // p1 is now nullptr
	std::cout << "p4: " << p4 << ", *p4: " << *p4 << ", p4.get(): " << p4.get() << ", p4.use_count(): " << p4.use_count() /* 2 */ << std::endl;

	// Unique user?
	// Note on .unique(): This function was deprecated in C++17 and removed in C++20 because use_count is only an approximation in multithreaded environment.
	// https://en.cppreference.com/w/cpp/memory/shared_ptr/unique
	std::cout << "unique owner?" << std::endl;
	std::cout << "p4: " << (p4.use_count() == (long) 1) << std::endl;
	std::cout << "p3: " << (p3.use_count() == (long) 1) << std::endl;

	// Swap (swaps the underlying values, and hence the use counts are effectively swapped too)
	std::cout << "swap: before" << std::endl;
	std::cout << "p2: " << p2 << ", *p2: " << *p2 << ", p2.get(): " << p2.get() << ", p2.use_count(): " << p2.use_count() /* 2 */ << std::endl;
	std::cout << "p3: " << p3 << ", *p3: " << *p3 << ", p3.get(): " << p3.get() << ", p3.use_count(): " << p3.use_count() /* 1 */ << std::endl;
	p2.swap(p3);
	std::cout << "swap: after" << std::endl;
	std::cout << "p2: " << p2 << ", *p2: " << *p2 << ", p2.get(): " << p2.get() << ", p2.use_count(): " << p2.use_count() /* 1 */ << std::endl;
	std::cout << "p3: " << p3 << ", *p3: " << *p3 << ", p3.get(): " << p3.get() << ", p3.use_count(): " << p3.use_count() /* 2 */ << std::endl;

	// Reinitialize to empty
	std::cout << "reinitialize to empty:" << std::endl;
	p4.reset();
	std::cout << "p4: " << p4 << std::endl;  // p4 is now nullptr

	return 0;
};

int main() {

	ex_b();
	ex_c();
	ex_d();

	return 0;
};