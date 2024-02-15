// Random number generation using boost.
// Boost has additional engines and distributions.
// Tobias Bilgeri, 05.01.2024
#pragma once
#include <iostream>
#include <boost/random.hpp>
#include <random>

int main() {

	using namespace boost::random;

	// ex a. rand nums w/ triangle distrib and lagged fibonacci engine.
	lagged_fibonacci44497 lagged_fibonacci(std::rand());
	triangle_distribution<double> triangle_dist(0.0, 0.5, 1.0);

	std::cout << "rand val from triangular distrib w/ lagged fibonacci engine: " << triangle_dist(lagged_fibonacci) << std::endl;

	// ex b. generate_canonical to create random number in [0, 1).
	//       the bits-parameter allows additional control over the degree / precision of randomness.
	std::cout << "generate_canonical with 8 bits: " << generate_canonical</*return type*/double, /*bits*/8>(lagged_fibonacci) << std::endl;
	std::cout << "generate_canonical with 16 bits: " << generate_canonical<double, 16>(lagged_fibonacci) << std::endl;
	std::cout << "generate_canonical with 32 bits: " << generate_canonical<double, 32>(lagged_fibonacci) << std::endl;
	std::cout << "generate_canonical with 64 bits: " << generate_canonical<double, 64>(lagged_fibonacci) << std::endl;
	std::cout << "generate_canonical with 128 bits: " << generate_canonical<double, 128>(lagged_fibonacci) << std::endl;
	std::cout << "generate_canonical with 256 bits: " << generate_canonical<double, 256>(lagged_fibonacci) << std::endl;
	std::cout << "generate_canonical with 512 bits: " << generate_canonical<double, 512>(lagged_fibonacci) << std::endl;
	std::cout << "generate_canonical with 1024 bits: " << generate_canonical<double, 1024>(lagged_fibonacci) << std::endl;
	// note on the bits parameter: N bits means we'll produce one of 2**N random variable.
	// hence, the bits parameter can be interpreted as a way to tweak how random the outcome
	// will ultimately be.

	// note that getting very small random numbers when using a small number of bits 
	// is apparently expected for lagged_fibonacci, see:
	// quantnet.com/threads/4-3-6-b-weird-result-with-lagged_fibonacci.49848/
	return 0;
}