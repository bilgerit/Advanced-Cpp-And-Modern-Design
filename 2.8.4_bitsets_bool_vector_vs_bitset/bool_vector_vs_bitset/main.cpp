// In this exercise, we compare std::vector<bool> with bitsets.
// As is shown below, it is clearly preferable to use bitsets when dealing with sets of bools.
// This is chiefly due to the fact that bitsets are specifically designed for this purpose and hence contain various features
// which are very convenient for handling sets of bits (such as bitwise operations via overloaded operators).
// The std::vector container (and other more general containers) does not have similar functionality simply for the fact that it is not
// specialized specifically for the purpose of handling individual bits.
// Tobias Bilgeri, 1. Dec. 2023
#pragma once
#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>


using BoolVec = std::vector<bool>;


BoolVec intersection(const BoolVec& v, const BoolVec& w) {
	// Compute the intersection of two BoolVec (std::vector containing bools) objects.
	BoolVec ans;
	for (unsigned int i = 0; i != v.size(); i++) {
		ans.push_back(
			v[i] && w[i] ? true : false
		);
	}
	return ans;
}


std::string boolvec2string(const BoolVec& v) {
	// Convert a BoolVec to a string.
	std::stringstream ss;
	for (auto i = v.begin(); i != v.end(); i++) {
		ss << *i;
	}
	return ss.str();
}


int ex_a() {
	// a) Determine which functionality it supports compared to the two bitset classes discussed here.

	BoolVec v(8, false);
	// The std::vector<bool> (defined as BoolVec herein) among other things equally keeps track of its size and allows for dynamic sizing via push_back.
	// More generally, it supports all the usual basic vector features.

	std::bitset<8> b{0};
	// the std::bitset objects on the other hand are heavily specialized for operations on individual bits and sets of bits.
	// Among other things, via member functions it supports operations such as .flip and .reset, which don't make sense 
	// and hence don't exist for more general containers such as the vector.
	// Furthermore, it is very easy to perform bitwise logical operations (as was shown in earlier exercises and is also demonstrated in exercise b),
	// as these things are handily implemented via overloaded operators.
	// Any such operations would require custom implementations via for example specialised derived classes of std::vector<bool> or free functions 
	// in order to be applied to std::vector<bool> objects.

	return 0;
};


int ex_b() {
	// b) Create a function to compute the intersection of two instances std::vector<bool>.
	
	// Definition of intersection of two bitsets: 
	// Intersection is a bitset and has same size as the two bitstream. 
	// Each element is 0 except if both bitsets are 1, for each index.
	//  => intersection == result of bitwise AND

	const unsigned int numElements{ 8 };

	// Test with bitsets first:
	std::bitset<numElements> b1{ 5UL };
	std::bitset<numElements> b2{ 25UL };

	auto b1b2Intersection = (b1 & b2); 

	std::cout 
		<< "Bitset 1: " << b1 
		<< ", Bitset 2: " << b2 
		<< ", Intersection: " << b1b2Intersection 
		<< std::endl;

	// Now with vectors:
	BoolVec v1(8, false);
	BoolVec v2(8, false);

	v1[7] = v1[5] = v2[3] = v2[4] = v2[7] = true;

	BoolVec v1v2Intersection = intersection(v1, v2);

	std::cout
		<< "Vector 1: " << boolvec2string(v1)
		<< ", Vector 2: " << boolvec2string(v2)
		<< ", Intersection: " << boolvec2string(v1v2Intersection)
		<< std::endl;

	return 0;
};



int main() {

	ex_a();
	ex_b();

	return 0;
};