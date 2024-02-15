// In this exercise, we explore bitsets further by performing logical operations on them, apply bitshifts, etc.
// Afterwards, we repead the same tasks for bytes, and also explore how to convert bytes to other types.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <iostream>
#include <bitset>
#include <string>
#include <boost/dynamic_bitset.hpp>


int main() {
	// a) Create two bitsets bs1 and bs2 (they must have the same number of bits, that is the same size).
	std::bitset<4> bs1{ 6 };
	std::bitset<4> bs2{ 7 };



	// b) Toggle all the bits of bs1 and bs2;
	bs1.flip();
	bs2.flip();



	// c) Perform bitwise XOR, OR and AND on bs1 and bs2.
	std::cout << "Bitset bs1: " << bs1.to_string() << std::endl;
	std::cout << "Bitset bs2: " << bs2.to_string() << std::endl;

	std::cout << "bitwise XOR: " << (bs1 ^ bs2) << std::endl;
	std::cout << "bitwise OR: " << (bs1 | bs2) << std::endl;
	std::cout << "bitwise AND: " << (bs1 & bs2) << std::endl;



	// d) Perform right and left shift operations on bs1 and bs2.
	std::cout << "Bitset bs1 + leftshift: " << (bs1 << 1) << std::endl;
	std::cout << "Bitset bs2 + leftshift: " << (bs2 << 1) << std::endl;
	std::cout << "Bitset bs1 + rightshift: " << (bs1 >> 1) << std::endl;
	std::cout << "Bitset bs2 + rightshift: " << (bs2 >> 1) << std::endl;



	// e) Use std::hash to create hashed values for bs1 and bs2.
	std::hash<std::bitset<4>> h1;
	std::hash<std::bitset<4>> h2;
	std::cout << "std::hash<std::bitset<4>> applied to bs1: " << h1(bs1) << std::endl;
	std::cout << "std::hash<std::bitset<4>> applied to bs1: " << h2(bs2) << std::endl;



	// f) Investigate how to create binary literals in C++ (since C++14) and their relationship with bitsets,
	//    for example:

	auto blit = 0b0011;  // integer

	std::byte b{ 0b0011 }; // Create from a binary literal

	std::bitset<4> bs(blit);  // bitset from int

	boost::dynamic_bitset<unsigned int> dbs(4); // all 0 by default
	dbs[1] = dbs[0] = 1;

	std::cout << "\nbyte: " << std::to_integer<int>(b) << '\n';
	std::cout << "bitset: " << bs << '\n';
	std::cout << "dynamic bitset: " << dbs << '\n';

	
	
	// g) Create a byte in different ways: from a binary literal, from an integer, as binary logical operators on existing bytes.
	std::byte byteFromBinaryLiteral{ 0b1010 };
	std::byte byteFromInteger{ (int) 10 };
	std::byte byteFromLogicalOp{b ^ byteFromBinaryLiteral};  // XOR
	
	std::cout << "Byte from binary literal: " << std::to_integer<int>(byteFromBinaryLiteral) << std::endl;
	std::cout << "Byte from integer: " << std::to_integer<int>(byteFromInteger) << std::endl;
	std::cout << "Byte from logical operation on existing bytes: " << std::to_integer<int>(byteFromLogicalOp) << std::endl;

	
	
	// h) Perform bitwise operations on bytes(AND, OR).
	std::cout << "Bitwise AND on 2 bytes: " << std::to_integer<int>(byteFromBinaryLiteral & byteFromLogicalOp) << std::endl;  // AND
	std::cout << "Bitwise OR on 2 bytes: " << std::to_integer<int>(byteFromBinaryLiteral | byteFromLogicalOp) << std::endl;  // OR

	
	
	// i) Perform left and right shift operations on bytes.Consider “extreme cases” of shifting.
	std::byte b1{ 1 };
	std::cout << "Original byte: " << std::to_integer<int>(b1)                 // 1
		<< ", \nafter right shift by 1: " << std::to_integer<int>(b1 >> 1)     // 0
		<< ", \nafter right shift by 100: " << std::to_integer<int>(b1 >> 100) // still 0
		<< ", \nafter left shift by 1: " << std::to_integer<int>(b1 << 1)      // 2
		<< ", \nafter left shift by 3: " << std::to_integer<int>(b1 << 3)      // 8
		<< ", \nafter left shift by 4: " << std::to_integer<int>(b1 << 4)      // 16 (maximum possible)
		<< ", \nafter left shift by 100: " << std::to_integer<int>(b1 << 100)  // 16 (still 16 since it's the maximum)
		<< std::endl;

	

	// j) Can you think of examples / applications where bytes and bitsets can be used, for example raw memory access and savings and performance improvements ?
	// Answer: In some cases, communication between servers and clients are done partially with raw bits.
	//         Here, it would probably be helpful to work with bits directly.


	return 0;
};