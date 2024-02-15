// We create a generic random number generator, and print the frequencies to terminal.
// Tobias Bilgeri, 05.01.2024
#pragma once
#include <iostream>
#include <list>
#include <random>
#include <string>
#include <map>

template <typename T>
void println(const T& printable) {
	std::cout << printable << "\n";
}

template <typename Dist, typename Eng> 
void GenerateRandomNumbers(Eng eng, Dist d, int32_t num_trials, const std::string& s) {
	// Take engine + distribution + num_trials + name, and generate a set of random
	// numbers stored in a map.
	// Then print the frequencies to termina.
	std::map<int64_t, int32_t> counts;

	for (int32_t i = 0; i != num_trials; i++) {
		counts[d(eng)] += 1;
	}

	println("Generated random numbers w/ Distribution " + s + " -- Frequencies:");
	for (const auto& [value, count] : counts) {
		println(std::to_string(value) + ": " + std::to_string(count));
	}
}

int main() {

	const int num_trials = 1000;
	std::mt19937 eng;
	
	auto geom = std::geometric_distribution<int32_t>(0.5);
	auto unif = std::uniform_int_distribution<int32_t>(1, 6);
	auto poisson = std::poisson_distribution<int32_t>(4.);

	GenerateRandomNumbers(eng, geom, num_trials, "Geometric");
	GenerateRandomNumbers(eng, unif, num_trials, "Uniform");
	GenerateRandomNumbers(eng, poisson, num_trials, "Poisson");
	
	// The distributions look as expected.
	// Geometric: frequencies decrease approx. w/ 0.5**n.
	// Uniform: frequencies are approx uniform.
	// Poisson w/ lambda = 4: Distribution looks like a 'skewed+bounded gaussian', as expected.

	return 0;
}