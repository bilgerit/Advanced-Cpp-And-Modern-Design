// Use MC to estimate Pi.
// Tobias Bilgeri, 06.01.2024
#pragma once
#include <iostream>
#include <random>
#include <cmath>


double computePi(int64_t NTrials) {
	// MC method to compute Pi.
	// Method: check if Pi lies within a quarter of a unit circle.

	auto eng = std::mt19937(42);
	auto distr = std::uniform_real_distribution<double>(0., 1.);

	int64_t count = 0;

	double x;
	double y;

	for (int64_t i = 0; i != NTrials; i++) {
		x = distr(eng);
		y = distr(eng);
		if (x * x + y * y <= 1.) {
			count += 1;
		}

	}

	// static cast to avoid getting 0.
	// (since NTrials > count, count/NTrials always yields 0 else.
	return static_cast<double>(count) / NTrials * 4.0;
}

int main() {
	
	int64_t NTrials = 100;
	double pi;

	for (int16_t i = 0; i != 7; i++) {
		NTrials *= 10;
		pi = computePi(NTrials);
		std::cout << "Trials: " << NTrials << ", Pi: " << pi << "\n";
	}

	// Result:
	//   Trials : 1000, Pi: 3.176
	//   Trials : 10000, Pi : 3.1512
 	//   Trials : 100000, Pi : 3.14236
	//   Trials : 1000000, Pi : 3.14037
	//   Trials : 10000000, Pi : 3.14116
	//   Trials : 100000000, Pi : 3.14158
	//   Trials : 1000000000, Pi: 3.14163
	// ... Hence, not even 1e8 elements (with seed 42) are enough to get 3.14159.

	return 0;
}