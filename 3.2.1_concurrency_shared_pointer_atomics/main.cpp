// In this exercise, we use smart pointers to demonstrate atomic_exchange operations on non-lock-free types.
// 
// IMPORTANT: std::atomic_exchange is deprecated in C++20 when used for std::shared_ptr<T> objects. Using C++17 for this exercise.
//            In C++20, we could for example just just directly create a std::atomic<std::shared_ptr<T>> type object instead, see:
//            https://en.cppreference.com/w/cpp/memory/shared_ptr/atomic2.
// 
// Tobias Bilgeri, 6. Dec. 2023
#pragma once
#include <iostream>
#include <atomic>
#include <cassert>

struct X {
	double val{ 0.0 };
	X() = default;
	void operator ()() const { std::cout << "An X " << val << std::endl; }
};

// C++11  
template<typename T> using GenericPointerType = std::shared_ptr<T>;
using PointerType = GenericPointerType<X>;

int main() {

	// Create smart pointer holding object of type X. Assign the instance of X a value.
	PointerType px1{ new X };
	px1->val = 1.;
	px1->operator()();

	// Create 2nd smart pointer and atomically exchange its value w/ the 1st smart pointer.
	PointerType px2{ new X };
	px2->val = 2.;
	std::atomic_exchange(&px1, px2);  // atomically replace the value of the 1st arg by the 2nd arg.
	px1->operator()();
	px2->operator()();

	// Create 3rd smart pointer and exchange again.
	PointerType px3{ new X };
	px3->val = 3.;
	std::atomic_exchange(&px2, px3);
	std::atomic_exchange(&px1, px3);
	px1->operator()();
	px2->operator()();
	px3->operator()();

	// Check use counts. They are equal to 3 in all cases, since they now all effectively point to the same underlying resource
	// (double of value 3 originally passed to px3).
	std::cout
		<< "\nUse count ptr 1: " << px1.use_count()
		<< "\nUse count ptr 2: " << px2.use_count()
		<< "\nUse count ptr 3: " << px3.use_count()
		<< std::endl;

	// Question: Why is atomic<std::shared_ptr> not possible?
	// Atomic objects must be trivially copyable, which is not the case for shared pointers in C++17.
	// In C++20 this became possible.
	assert(std::is_trivially_copyable_v<PointerType> == false);

	// Question: Are shared pointers lock-free?
	// No. Only certain types such as std::atomic<int> are look free (depends on platform and compiler).
	assert(std::atomic_is_lock_free(&px1) == false);

	return 0;
};