// In this exercise, we demonstrate the template method pattern (TMP).
// In this pattern, a class defines a 'skeleton logic', and the precise behaviour can be flexibly changed (in this case by
// supplying function objects (lambdas herein) to the constructor defining the precise behaviour).
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include "util.h"


int main() {
	std::size_t n = 4;
	double startValue = 1.5;
	double multiplier = 3.0;
	InputFunction iFunction = [multiplier]() -> double {return multiplier; };
	OutputFunction oFunction = [](const std::vector<double>& v) -> void {
		std::cout << "Sending to output the following vector: [";
		for (const auto& el : v) {
			std::cout << el << " ";
		}
		std::cout << "]" << std::endl;
	};

	std::cout << "Input params: n=" << n << ", startValue=" << startValue << ", multiplier=" << multiplier << std::endl;
	TMPClass tmp_object(n, startValue, iFunction, oFunction);
	tmp_object.run();
	return 0;
}