// In this exercise, we demonstrate various ways of initializing a class and a struct object: 
// default (no arguments supplied to constructor), value (empty curly braces), direct, copy, list initialization, aggregate initialization, reference initialization.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include "util.h"


void ex_1() {
	// Default Initialization
	SimpleClass<int> default_initialized;
	default_initialized.print();

	// Value Initialization
	SimpleClass<int> value_initialized{};
	value_initialized.print();

	// Direct Initialization
	int i{ 42 };
	vector<int> v{ 1, 2, 3 };
	SimpleClass directly_initialized{ i, v };
	directly_initialized.print();

	// Copy Initialization
	auto copy_initialized{ directly_initialized };
	copy_initialized.print();

	// List Initialization
	SimpleClass<int> list_initialized({ 42, {1, 2, 3} });
	list_initialized.print();

	// Aggregate Initialization
	SimpleClass aggregate_initialized = { 42, {1, 2, 3} };
	aggregate_initialized.print();

	// Reference Initialization
	SimpleClass<int>& reference_initialized = aggregate_initialized;
	reference_initialized.print();


	// Alternatively, using move:
	// 	auto copy_initialized = std::move(directly_initialized);
	// directly_initialized.print()  ........ this will now show an empty vector.

	// Can also use auto&& (will bind to lvalues and rvalues):
	// auto&& point1 = SimpleClass{ directly_initialized };

}



void ex_2() {
	// Ill-defined cases
	// SimpleClass s = 5;   // makes no sense to purely equate it to a primitive 
	// SimpleClass s{ 1 };  // no constructor defined for this input
	// etc. ...
}



void ex_3() {
	S s_default_initialized;
	s_default_initialized.print();

	S s_value_initialized{};
	s_value_initialized.print();
	
	int a[3] = { 4, 5, 6 };
	S s_directly_initialized{ 1, {2, 3, *a} };
	s_directly_initialized.print();

	// Copy initialization --- no copy constructor was given.

	S s_list_initialized({ 1, {2, 3, {4, 5, 6}} });
	s_list_initialized.print();

	S s_aggregate_initialized = { 1, {2, 3, {4, 5, 6}} };
	s_aggregate_initialized.print();

	S& s_reference_initialized = s_aggregate_initialized;
	s_reference_initialized.print();
}


int main() {
	ex_1();
	ex_2();
	ex_3();

	return 0;
}
