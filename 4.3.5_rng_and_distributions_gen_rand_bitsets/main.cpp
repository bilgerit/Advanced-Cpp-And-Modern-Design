// Generating random Bits and Bitsets (instead of random int / float / ...).
// Tobias Bilgeri, 06.01.2024
#pragma once
#include <iostream>
#include <bitset>
#include <random>
#include <chrono>
#include <array>


// ex. b. function impl
template<uint64_t width>
double test_random_bits(uint64_t trials) {

	// create an engine for generation of independent random bits.
	std::mt19937 gen(42);
	std::independent_bits_engine<std::mt19937, width, uint64_t> engine(gen);

	uint64_t count = 0;

	for (int i = 0; i < trials; i++) {
		// create random bits and assign to decimal type.
		uint64_t rand_val = engine();
		// convert decimal type to bitset.
		std::bitset<width> bits(rand_val);
		// count number of bits equal to 1.
		count += bits.count();
	}

	// return fraction of all generated bits which were equal to 1.
	// this should be approx 0.5 (since prob of 0 and 1 is equal).
	return static_cast<double>(count) / (width * trials);
}


int main() {

	// ex. a.
	{
		// create an engine for generation of independent random bits.
		std::mt19937 mt(42);
		std::independent_bits_engine<std::mt19937, 32, uint32_t> engine(mt);

		// create random bits and assign to uint32_t type.
		uint32_t rand_val = engine();
		// convert uint32_t to bitset of 32 bits
		std::bitset<32> bits(rand_val);

		std::cout << "Generated random value: " << rand_val << ", Bitset: " << bits << std::endl;
	}

	// ex. b + c.
	{
		// create bitsets of different sizes.
		// the fraction of random bits equal to 1 should be around 0.5 (true everywhere).
		// however, for a small number of trials, we can see that when we create a larger
		// number of bits at each trial, we converge to 0.5 more quickly.
		std::cout << "width=2, ratio=" << test_random_bits<2>(1'000) << std::endl;
		std::cout << "width=8, ratio=" << test_random_bits<8>(1'000) << std::endl;
		std::cout << "width=16, ratio=" << test_random_bits<16>(1'000) << std::endl;
		std::cout << "width=64, ratio=" << test_random_bits<64>(1'000) << std::endl;
	}

	return 0;
}