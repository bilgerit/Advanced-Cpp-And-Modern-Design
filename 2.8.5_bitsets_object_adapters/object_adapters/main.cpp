// In this exercise, we create a BitMatrix class which emulates std::bitset behaviour but on a MxN matrix level.
// See BitMatrix.h for details.
// Tobias Bilgeri, 1. Dec. 2023
#pragma once
#include "BitMatrix.h"


int main() {
	// Here we test (via observation in terminal) the correctness of various features of the BitMatrix class.

	// Default Constructor.
	const size_t numRows{ 3 };
	const size_t numCols{ 4 };
	BitMatrix<numCols, numRows> b;

	std::cout << "Default initialized BitMatrix: " << std::endl;
	b.print();

	std::cout << "Set all: " << std::endl;
	b.set();
	b.print();

	std::cout << "Reset all: " << std::endl;
	b.reset();
	b.print();

	std::cout << "Set 1st row: " << std::endl;
	b.set(1);
	b.print();

	std::cout << "Flip 2nd row: " << std::endl;
	b.flip(2);
	b.print();

	std::cout << "Operations on Whole Matrix: any=" << b.any() << ", none=" << b.none() << ", all=" << b.all() << ", count=" << b.count() << std::endl;
	std::cout << "Operations on 1st row: any=" << b.any(1) << ", none=" << b.none(1) << ", all=" << b.all(1) << ", count=" << b.count(1) << std::endl;

	// Copy construct
	auto b2{ b };
	
	std::cout << "Copy-construct new matrix and flip whole matrix: " << std::endl;
	b2.flip();
	b2.print();

	std::cout << "Apply OR and print: " << std::endl;
	(b.OR(b2)).print();

	std::cout << "Apply XOR and print: " << std::endl;
	(b.XOR(b2)).print();

	std::cout << "Apply AND and print: " << std::endl;
	(b.AND(b2)).print();

	// Move assignment
	auto b3 = std::move(b2);
	std::cout << "Old matrix after move assignment: " << std::endl;
	b2.print();
	std::cout << "New matrix after move assignment: " << std::endl;
	b3.print();

	return 0;
};