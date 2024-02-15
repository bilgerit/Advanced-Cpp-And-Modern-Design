// Simple helper file containing utility needed for this exercise, most importantly the functions to display the types of various objects.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <type_traits>


template <typename T>
void find_type_a(const T& t) {
	// check if input is pointer, null pointer, lvalue ref or rvalue ref, and print the result to console.
	if (std::is_pointer<T>::value) {
		std::cout << "this is a pointer" << std::endl;
	} else if (std::is_null_pointer<T>::value) {
		std::cout << "this is a null pointer" << std::endl;
	} else if (std::is_lvalue_reference<T>::value) {
		std::cout << "this is a lvalue reference" << std::endl;
	} else if (std::is_rvalue_reference<T>::value) {
		std::cout << "this is a rvalue reference" << std::endl;
	} else {
		std::cout << "this is a value" << std::endl;
	}
};


template <typename T>
void find_type_b(const T& t) {
	// check if input is a member function pointer or pointer to a non-static member object, and print the result to console.
	if (std::is_member_function_pointer_v<T>) {
		std::cout << "this is a member function pointer" << std::endl;
	} else if (std::is_member_object_pointer_v<T>) {
		std::cout << "this is a pointer to a non-static member object" << std::endl;
	} else {
		std::cout << "this is not a member function pointer or pointer to a non-static member object" << std::endl;
	}

}


class MyClass {
	// Dummy class for this exercise.
public:
	void func() {};
	int a;
};
