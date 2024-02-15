// In this exercise, we implement a 'switchable bridge', wherein we create functions that support both pointers and scalar references.
// We then go on to print the underlying value of a value / scalar reference, pointer, and smart pointer, making use of the bridge.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <type_traits>


template<typename T>
void print(const T& t, std::true_type)
{
	// Print the value of the pointer.
	std::cout << "Printing dereferenced pointer value:" << *t << std::endl;
}


template<typename T>
void print(const T& t, std::false_type)
{
	// Print the value of the scalar reference.
	std::cout << "Printing scalar reference value: " << t << std::endl;
}


template<typename T>
void print(const T& t)
{
	// Bridge: Call the correct function based on the type of T.
	// Here, prints the underlying value of a pointer or a scalar reference.
	print(t, std::is_pointer<T>());
}


int main() {
	int a{ 111 };
	int* b = new int(222);
	auto c = std::make_shared<int>(333);

	print(a);
	print(b);
	print(c);  // smart pointer is considered as value. Can just print its value directly without needing to do an explicit dereferencing.
	print(c.get());  // .(get) returns the underlying pointer, hence we use to pointer printing method.

	return 0;
};