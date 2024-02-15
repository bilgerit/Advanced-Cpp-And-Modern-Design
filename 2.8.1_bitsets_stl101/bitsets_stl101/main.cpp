// In this exercise, we learn the basics of std::bitset, such as:
// How to create them in different ways, how to alter them, and how to convert them to other types.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <bitset>
#include <iostream>
#include <cassert>
#include <string>
#include <stdexcept>


int main() {

	// a) Create bitsets from unsigned long and unsigned long long.

	// create primitives first
	unsigned long ul{ 8 }; 
	unsigned long long ull{ 8 };

	// create bitsets from primitives
	std::bitset<4> bul(ul);        
	std::bitset<4> bull(ull);

	// check hat unsigned long and unsigned long long let to same bitset:
	assert(bul == bull);



	// b) Create bitsets from full strings(for example, “01010”).Create a bitset from parts of strings based on a start index and the number of bits to use.
	// 
	// create bitset from string representing bits
	std::bitset<4> bs{ "1000" };   
	assert(bs == bul);

	// create bitset from string representing bits w/ specific start index and length
	unsigned int startIdx{ 4 };
	const int numBits{ 4 };
	std::bitset<numBits> bs2{ std::string("0000100000"),  startIdx, numBits};   
	assert(bs2 == bul);

	// create bitset from string representing bits w/ specific start index only
	std::bitset<numBits> bs3{ std::string("00001000"),  startIdx };
	assert(bs3 == bul);



	// c) In the case of strings(for example), use exception handling to check for out - of - range values and invalid arguments(bits that are neither 0 nor 1).
	
	
	// this will give out of range error (startIdx is larger than size of string)
	try {
		std::bitset<4> bs4{ std::string("1"), startIdx };
	}
	catch (const std::out_of_range& e){
		std::cout << e.what() << std::endl;
	}

	// this will give invalid argument error (bit string contains 2)
	try {
		std::bitset<4> bs5{ std::string("2") };
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
	}



	// d) Set the bits in a bitset in different ways:
	//    • Set / reset all bits.
    //    • Flip the bits.
	//    • Test if none, all or any bits are set.
	//    • Access the elements.
	//    • Count the number of set bits.

	// Here I use a single bit to test these things:
	std::bitset<1> bs6;

	// sets everyting to 1
	bs6.set();  
	assert(bs6 == 1);

	// sets everything to 0
	bs6.reset();  
	assert(bs6 == 0);

	// sets all 0s to 1s and vice versa
	bs6.flip();  
	assert(bs6 == 1);

	assert(bs6.none() == false);  // check if all are 0
	assert(bs6.all() == true);    // check if all are 1
	assert(bs6.any() == true);    // check if any is 1

	auto el = bs6[0];  // type: std::bitset<1Ui64>::reference.
	int intEl{ el };                          // can convert the element to int, for example.
	assert(intEl == 1);

	assert(bs6.count() == 1);  // count elements in bitset



	// e) Convert a bitset to std::string, unsigned long and unsigned long long.
	std::bitset<4> bs7{ "1010" };
	std::string bs7ToString = bs7.to_string();
	unsigned long bs7ToUnsignedLong = bs7.to_ulong();
	unsigned long long bs7ToUnsignedLongLong = bs7.to_ullong();



	// f) Test if two bitsets are equal or unequal.
	std::cout << "bitset 1: " << bs2 << ", bitset 2: " << bs3 << ", are equal: " << std::boolalpha << (bs2 == bs3) << std::endl;
	std::cout << "bitset 1: " << bs2 << ", bitset 2: " << bs7 << ", are equal: " << std::boolalpha << (bs2 == bs7) << std::endl;

	return 0;
};