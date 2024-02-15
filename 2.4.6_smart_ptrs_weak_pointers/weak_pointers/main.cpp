// In this exercise, we take a look at the weak pointer, which is an observer of smart pointers.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <memory>
#include <iostream>


int ex_a() {
	// Create a shared pointer, print the use count and then create a weak pointer that observes it. Print the use count again.

	std::cout << "Exercise a)" << std::endl;

	std::shared_ptr<int> sptr = std::make_shared<int>(1);
	std::cout << sptr.use_count() << "\n";  // 1
	std::weak_ptr<int> wptr(sptr);  // weak pointer pointing to shared pointer holding integer pointer
	std::cout << sptr.use_count() << std::endl;  // still 1

	return 0;
};


int ex_b() {
	// Assign a weak pointer to a shared pointer and check that the weak pointer is not empty.

	std::cout << "\nExercise a)" << std::endl;

	std::weak_ptr<int> wptr;
	auto sptr(wptr.lock());  // .lock() creates a new shared ptr object that shares ownership of the object managed by the weak pointer
	std::cout << "wptr is empty? " << std::boolalpha << wptr.expired() << std::endl;
	std::cout << "sptr use count: " << sptr.use_count() << ", sptr value: " << sptr.get() << std::endl;

	return 0;
};


int ex_c() {
	// Assign a weak pointer to another weak pointer; assign a weak pointer to shared pointer. What is the use count in both cases?

	std::cout << "\nExercise c)" << std::endl;

	std::weak_ptr<int> wptr1;
	std::weak_ptr<int> wptr2(wptr1);
	std::weak_ptr<int> wptr3;
	std::shared_ptr<int> sptr(wptr3.lock());
	std::cout << "use count wptr1: " << wptr1.use_count() << ", use count wptr2: " << wptr2.use_count() /* 0 */ << std::endl;
	std::cout << "use count wptr3: " << wptr3.use_count() << ", use count sptr: " << sptr.use_count() /* 0 */ << std::endl;
	return 0;
};


int main() {

	ex_a();
	ex_b();
	ex_c();

	return 0;
};