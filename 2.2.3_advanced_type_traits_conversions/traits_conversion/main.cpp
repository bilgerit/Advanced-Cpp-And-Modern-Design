// In this exercise, we take a look at type specifiers and their conversions: unsigned, const, volatile.
// We also look at examples of CTAD, decltype, and type dependency in list initialization.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include "util.h"


int main() {
	int myInt{ 5 };
	unsigned int myUnsignedInt{ 5 };
	const double myDouble{ 5 };
	const int myConstInt{ 5 };
	volatile int myVolatileInt{ 5 };

	// signed_conversion
	std::cout << "signed_conversion" << std::endl;
	std::cout << typeid(myInt).name() << " " << myInt << " -> " << typeid(signed_conversion(myInt)).name() << " " << signed_conversion(myInt) << std::endl;
	std::cout << typeid(myUnsignedInt).name() << " " << myUnsignedInt << " -> " << typeid(signed_conversion(myUnsignedInt)).name() << " " << signed_conversion(myUnsignedInt) << std::endl;

	// const_conversion
	std::cout << "const_conversion" << std::endl;
	std::cout << std::boolalpha << "is const: " << std::is_const<decltype(myInt)>::value << " -> " << std::is_const<decltype(const_specifier_conversion(myInt))>::value << std::endl;
	std::cout << std::boolalpha << "is const: " << std::is_const<decltype(myConstInt)>::value << " -> " << std::is_const<decltype(const_specifier_conversion(myConstInt))>::value << std::endl;
	std::cout << std::boolalpha << "is const: " << std::is_const<decltype(myDouble)>::value << " -> " << std::is_const<decltype(const_specifier_conversion(myDouble))>::value << std::endl;

	// volatile_conversion
	std::cout << "volatile_conversion" << std::endl;
	std::cout << std::boolalpha << "is volatile: " << std::is_volatile<decltype(myInt)>::value << " -> " << std::is_volatile<decltype(volatile_specifier_conversion(myInt))>::value << std::endl;
	std::cout << std::boolalpha << "is volatile: " << std::is_volatile<decltype(myVolatileInt)>::value << " -> " << std::is_volatile<decltype(volatile_specifier_conversion(myVolatileInt))>::value << std::endl;


	// Discuss the difference between direct list initialisation and copy list initialisation in C++17/20 compared to C++11.
	//   Answer:
	//      The main difference is that in C++17, we can use the auto keyword to deduce the type of a variable from its initializer list.
	//      The direct list initialization is also explicitly used to initialize a variable, whereas with copy, we may also get a initializer_list type.
	// In which case does auto deduction reduce to std::initializer_list? 
	//   Answer:
	//      If all elements have the same type.
	// Give a code example. 
	// Under which circumstances can we get ill-formed expressions?
	//   Answer:
	//      If the elements have different types.

	int x{ 5 };
	auto y{ 5 };  // initializes to int by default
	auto z = { 1, 2}; // initializes to std::initializer_list<int>
	// auto a { 1, 2};  // not working -- compiler doesn't know how to handle the multipe values to initialize y
	// auto a = { 1, 1.5};  // not working -- compiler doesn't know how to handle the different types (1.5 vs 1?).


	// Discuss how Class Template Argument Deduction (CTAD)) reduces code verbosity. 
	//   Answer:
	//       We don't have to specify the template arguments anymore for cases where the compiler can deduce the types from the arguments.
	// Give a non-trivial example using std::tuple and a user-defined class.
	
	class MyClass {};
	MyClass myObject;

	// CTAD: make_tuple automatically deduces the types (int, double, MyClass)
	auto myTuple = std::make_tuple(myInt, myDouble, myObject);  
	static_assert(std::is_same_v<decltype(myTuple), std::tuple<int, double, MyClass>>); 


	// Investigate the applicability of decltype and std::is_same when comparing the type of a result with a “target” type.
	bool is_same{std::is_same_v<decltype(myInt * myDouble), double>};
	std::cout << std::boolalpha << "multiplying int and double type objects, and then checking result type against double using std::is_same and decltype: " 
		<< is_same << std::endl;
	static_assert(std::is_same_v<decltype(myInt * myDouble), double>);

	return 0;
};