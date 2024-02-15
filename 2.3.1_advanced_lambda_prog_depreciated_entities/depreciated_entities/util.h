// Simple helper file containing utility needed for this exercise.
// Herein we define functions, classes, enums, lambdas, etc., as depreciated.
// In the main file we then show how calling them leads to errors.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <iostream>


[[deprecated("deprecated my_free_func() called")]] void my_free_func() {
	std::cout << "Free function called" << std::endl;
};


class [[deprecated("deprecated MyClassDepr called")]] MyClassDepr {};


class MyClass {
public:
	[[deprecated("deprecated member fct called")]] void my_member_func() {
		std::cout << "deprecated member function called" << std::endl;
	};
};


[[deprecated("deprecated global var used")]] int deprecated_var;


enum [[deprecated("deprecated enum used")]] MyEnum {
	ENUM1,
	ENUM2
};


template <typename T>
class MyTemplateClass {};


template <>
class [[deprecated("deprecated template class specification used")]] MyTemplateClass<int> {};


[[deprecated("deprecated lambda called")]]  auto my_lambda = []() {
	std::cout << "deprecated lambda called" << std::endl;
};
