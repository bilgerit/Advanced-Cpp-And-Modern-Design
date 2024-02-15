// This exercise serves as an introduction to type_traits and how to find the different types of various objects.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include "util.h"


int ex_a() {
	// Print types of various objects using: plain value, pointer, null ptr, lvalue ref, rvalue ref.

	int value;
	int* value_ptr;
	int* null_ptr = nullptr;
	int& lvalue_ref = value;
	int&& rvalue_ref = 5;

	std::cout << "\n\nExercise A\n";
	find_type_a(value);       // value
	find_type_a(lvalue_ref); // value (due to conversion)
	find_type_a(rvalue_ref); // value (due to conversion)
	find_type_a(std::move(value)); // value (due to conversion)

	find_type_a(value_ptr);     // ptr
	find_type_a(null_ptr);      // ptr (due to conversion)
	find_type_a(&value);     // ptr (due to conversion)

	find_type_a<std::nullptr_t>(nullptr); // null_ptr

	find_type_a<int&>(lvalue_ref);  // lvalue
	find_type_a<int&&>(rvalue_ref);  // rvalue


	return 0;
};


int ex_b() {
	// Find types of class members.
	std::cout << "\n\nExercise B\n";
	auto member_fct_ptr = &MyClass::func;
	auto member_var_ptr = &MyClass::a;
	find_type_b(member_fct_ptr); // member fct
	find_type_b(member_var_ptr); // pointer to non-static member object

	return 0;
};


int ex_c() {
	// Find types of smart pointers.
	std::cout << "\n\nExercise C\n";
	auto shared_ptr = std::make_shared<int>();
	auto raw_ptr = shared_ptr.get();
	find_type_a(shared_ptr);   // Value
 	find_type_a(raw_ptr);      // Pointer
	return 0;
};


int main() {

	ex_a();
	ex_b();
	ex_c();

	return 0;
};