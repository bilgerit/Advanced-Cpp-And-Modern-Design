// In this exercise, we explore dynamic bitsets provided via boost.
// On top of functionality provided by std::bitset, they also allow for dynamic runtime behaviour such as resize, clear, push_back, pop_back, append, etc.
// Other than that, dynamic_bitset possess mostly the same member functions as bitset, and behaves mostly the same as bitset.
// Noteably, the constructor behaves slightly different (see below). The size of the bitset is now a variable.
// For std::bitset, the size was a template argument, and hence was known at compile time.
// Tobias Bilgeri, 30 Nov. 2023
#pragma once
#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <string>


int ex_a() {
	// a) Port the code that you created in questions 1 and 2 to boost::dynamic_bitset<T>. Test your code.

	std::cout << "\n\nExercise A\n\n" << std::endl;

	// Different ways of creating the dynamic bitset: from unsigned long, unsigned long long, string, binary literal
	
	unsigned long ul{ 4 };
	unsigned long long ull{ 6 };  // not accepted in dynamic_bitset -- see below
	std::string s{ "10101" };

	// this wont give binary represenation of ul -- instead, ul will specify the number of bits (different from std::bitset)
	// boost::dynamic_bitset<> b1{ ul };
	// have to provide number of bits explicitly, and then optionally how to configure the bits.
	boost::dynamic_bitset<> b1{ 5, ul };

	// dynamic_bitset doesn't accept unsigned long long in the constructor
	// boost::dynamic_bitset<> b2{ 5, ull };
	boost::dynamic_bitset<> b2{ 5, 6ul };
	boost::dynamic_bitset<> b3{ s };
	boost::dynamic_bitset<> b4{ s, 1, 3 };
	boost::dynamic_bitset<> b5{ 4, 0b1010 };  // also when explicitly passing binary literal, we need to specify then number of elements.

	std::cout << "Bitset b1: " << b1 << std::endl;
	std::cout << "Bitset b2: " << b2 << std::endl;
	std::cout << "Bitset b3: " << b3 << std::endl;
	std::cout << "Bitset b4: " << b4 << std::endl;
	std::cout << "Bitset b5: " << b5 << std::endl;

	// Test member methods: reset, flip, all, none, any, count
	// (same as for std::bitset)
	b1.reset();
	std::cout << "Bitset b1 after reset: " << b1 << std::endl;

	b2.flip();
	std::cout << "Bitset b2 after flip: " << b2 << std::endl;

	std::cout << "Bitset b2.all(): " << b2.all() << std::endl;
	std::cout << "Bitset b2.none(): " << b2.none() << std::endl;
	std::cout << "Bitset b2.any(): " << b2.any() << std::endl;
	std::cout << "Bitset b2.count(): " << b2.count() << std::endl;

	// Test accessing member & conversion to int
	// (Index is counted from the right (LSB), same as for std::bitset)
	auto el = b2[1];
	int elToInt{ el };
	std::cout << "Bitset b2[1]: " << el << std::endl;

	// Test conversions of the whole dynamic_bitset
	unsigned long ul2 = b2.to_ulong();
	std::cout << "Bitset b2.to_ulong(): " << ul2 << std::endl;

	std::string s2;
	to_string(b2, s2);
	std::cout << "Bitset b2 converted to string: " << s2 << std::endl;

	// Logic operation (same as for std::bitset)
	std::cout << "b1==b2: " << (b1 == b2) << std::endl;

	// Bitwise logic operations (same as for std::bitset)
	std::cout << "b1 ^ b2: " << (b1 ^ b2) << std::endl;  // XOR
	std::cout << "b1 | b2: " << (b1 | b2) << std::endl;  // OR
	std::cout << "b1 & b2: " << (b1 & b2) << std::endl;  // AND

	std::cout << "b2 << 1: " << (b2 << 1) << std::endl;
	std::cout << "b2 >> 1: " << (b2 >> 1) << std::endl;

	return 0;
};


int ex_b() {
	// b) (Changing the size of a bitset at run-time)
	//    Apply resize(), clear(), push_back(), pop_back() and append() to bitset instances.

	std::cout << "\n\nExercise B\n\n" << std::endl;

	boost::dynamic_bitset<> b{std::string("00110011")};

	std::cout << "Bitset b=" << b << std::endl;

	b.resize(6);  // drops the two left-most elements, since bitsets always work from right to left.
	std::cout << "After b.resize(6): b=" << b << std::endl;

	b.clear();  // removes any bits (i.e., doesn't just set them to 0, but fully removes them)
	std::cout << "After b.clear(): b=" << b << std::endl;

	b.push_back(1); // adds bits on the right (i.e., at the MSB)
	std::cout << "After b.push_back(1): b=" << b << std::endl;

	b.push_back(3);
	std::cout << "After b.push_back(3): b=" << b << std::endl;

	b.push_back(true);
	std::cout << "After b.push_back(true): b=" << b << std::endl;

	b.push_back(false);
	std::cout << "After b.push_back(false): b=" << b << std::endl;

	b.pop_back();
	std::cout << "After b.pop_back(): b=" << b << std::endl;

	b.append(4);  // adds 4 (100) from the right.
	std::cout << "After b.append(4): b=" << b << std::endl;


	return 0;
};


int ex_c() {
	// c) (Set operations)
	//    Test the functionality to test if a bitset is a subset (or proper subset) of another bitset.

	std::cout << "\n\nExercise C\n\n" << std::endl;

	boost::dynamic_bitset<> b1{std::string("001100")};
	boost::dynamic_bitset<> b2{ std::string("110011") };
	boost::dynamic_bitset<> b3{ std::string("111111") };
	std::cout << "Bitset 1: " << b1 << ", Bitset 2: " << b2 << ", Bitset 3: " << b3
		<< "; \nb2 is subset of b1: " << std::boolalpha << b2.is_subset_of(b1) // False
		<< "; \nb1 is subset of b2: " << b1.is_subset_of(b2) // False
		<< "; \nb3 is subset of b2: " << b3.is_subset_of(b2) // False
		<< "; \nb2 is subset of b3: " << b2.is_subset_of(b3) // True (since for every bit set in b2, the bit is set in b3)
		<< "; \nb1 is subset of b3: " << b1.is_subset_of(b3) // True (since for every bit set in b1, the bit is set in b3)
		<< std::endl;

	return 0;
};


int ex_d() {
	// d) (Searching in bitsets)
	//    Use find_first() and find_next() to search for bits in bitsets.

	std::cout << "\n\nExercise D\n\n" << std::endl;

	boost::dynamic_bitset<> b{ std::string("101010") };

	// Note that the result of b.find_first() is 1, since we are starting to search from the right.
	std::cout << "Bitset: " << b << ", find_first(): " << b.find_first() << ", find_next(b.find_first()): " << b.find_next(b.find_first()) << std::endl;

	return 0;
}

int main() {

	ex_a();
	ex_b();
	ex_c();
	ex_d();

	return 0;
};