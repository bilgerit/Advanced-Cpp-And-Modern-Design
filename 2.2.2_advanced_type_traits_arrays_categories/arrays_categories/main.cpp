// In this exercise, we look at some type traits of arrays: is_array, rank, extend. Later on, we remove extends and check the results.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <array>
#include <vector>
#include <type_traits>
#include <iostream>
#include <string>



int ex_a() {
	// Exercise a: apply std::is_array<T> to various types
	std::cout << "Exercise a: apply std::is_array<T> to various types." << std::endl;

	std::cout << std::is_array<int[3]>::value << std::endl; // true -- as this is a c-style array
	std::cout << std::is_array<std::array<int, 3>>::value << std::endl;  // false -- as this is a std::array

	class MyClass {};

	std::cout << std::is_array<MyClass>::value << std::endl;  // false
	std::cout << std::is_array<int>::value << std::endl;  // false
	std::cout << std::is_array<std::vector<int>>::value << std::endl;  // false
	std::cout << std::is_array<std::vector<std::vector<int>>>::value << std::endl;  // false
	std::cout << std::is_array<std::array<std::array<int, 3>, 3>>::value << std::endl;  // false
	std::cout << std::is_array<std::string>::value << std::endl;  // false
	std::cout << std::is_array<bool>::value << std::endl;  // false
	std::cout << std::is_array<char>::value << std::endl;  // false

	return 0;
};


int ex_b() {
	// Exercise b: apply rank and extent to ArrayType int[]p[3][4][5]
	std::cout << "\n\nExercise b: apply rank and extent to ArrayType int[]p[3][4][5]" << std::endl;

	using ArrayType = int[][3][4][5];
	std::cout << std::rank<ArrayType>::value << std::endl;  // 4
	std::cout << std::extent<ArrayType, 0>::value << std::endl;  // 0
	std::cout << std::extent<ArrayType, 1>::value << std::endl;  // 3
	std::cout << std::extent<ArrayType, 2>::value << std::endl;  // 4
	std::cout << std::extent<ArrayType, 3>::value << std::endl;  // 5

	return 0;
};


int ex_c() {
	// Exercise c: check what happens when we remove extents.
	std::cout << "\n\nExercise c: check what happens when we remove extents." << std::endl;

	using ArrayType = int[][3][4][5];
	using ArrayTypeRemoved1 = std::remove_extent<ArrayType>::type;  
	using ArrayTypeRemovedAll = std::remove_all_extents<ArrayType>::type;  

	std::cout << std::extent<ArrayTypeRemoved1>::value << std::endl;  // 3
	std::cout << std::extent<ArrayTypeRemovedAll>::value << std::endl;  // 0

	std::cout << "is array the same as int after removing extent? " << std::is_same<int, ArrayTypeRemoved1>::value << std::endl;  // False
	std::cout << "is array the same as int after removing all extent? " << std::is_same<int, ArrayTypeRemovedAll>::value << std::endl;  // True


	return 0;
};


int main() {

	ex_a();
	ex_b();
	ex_c();

	return 0;
};