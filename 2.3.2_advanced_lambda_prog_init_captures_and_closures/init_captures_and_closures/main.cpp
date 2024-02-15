// In this exercise, we explore different ways of capturing variables in lambda functions making use of C++11 and C++14 features including move semantics.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <functional>

int ex_a() {
	// Lambda functions: Compare default capture with move semantics based capture.
	std::cout << "Excercise A\n";

	int size = 4;
	double val = 2.71;
	std::vector<double> data(size, val);  // homogeneous initialization of vector.

	// Default capture mode (not preferred)
	auto fun = [&data]() mutable {
		// lambda fn w/ reference capture. Sets every element to 3.14.
		for (std::size_t i = 0; i < data.size(); ++i) {
			data[i] = 3.14;
			std::cout << data[i] << ",";
		}
		std::cout << '\n';
		};

	fun();

	// 'data' still exists and has been modified. Everything is set to 3.14 now.
	for (std::size_t i = 0; i < data.size(); ++i) {
		// data[i] = 3.14;
		std::cout << data[i] << ":";
	}
	std::cout << std::endl;

	// Now with move semantics
	auto fun_move = [data = std::move(data)]() mutable {
		// lambda fn w/ move semantics. Sets every element to 4.14. Original data vector will now be empty, since its content has been moved.
		for (std::size_t i = 0; i < data.size(); ++i) {
			data[i] = 4.14;
			std::cout << data[i] << ",";
		}
		std::cout << '\n';
		};

	fun_move();

	// 'data' now has size 0.
	std::cout << data.size() << std::endl;

	return 0;
};

int ex_b() {
	// C++14 init capture with local variables

	std::cout << "\nExcercise B\n\n";

	int x = 1'000'000; // This is a digit separator

	auto fun4 = [&r = x]() {
		// lambda fn squaring the reference-captured value x.
		r *= 2;
		std::cout << "\nr: " << r;
		};

	fun4();
	std::cout << std::endl;
	return 0;
};

int ex_c() {
	// Emulating generalized lambda capture with C++11

	std::cout << "\nExcercise C\n\n";

	int size2 = 3;
	double val2 = 1.41;
	std::vector<double> data2(size2, val2);
	std::array<double, 3> data3 = { 1.2, 2.4, 4.7 };

	/*
	// Original code which uses std::bind:

	auto fun3 = std::bind(
		[](std::vector<double>& array, std::array<double, 3> array2) {
			for (std::size_t i = 0; i < array.size(); ++i) {
				array[i] = 3.14;
				std::cout << array[i] << "/";
			}
			std::cout << '\n';
			for (std::size_t i = 0; i < array2.size(); ++i) {
				array2[i] = 2.71;
				std::cout << array2[i] << "/";
			}
		},
		std::move(data2),
		std::move(data3)
	);
	*/
	// Modified code which uses a modern lambda function w/ move-semantics based capture
	auto fun3 = [array = std::move(data2), array2 = std::move(data3)]() {
		// Capture two arrays by value using move semantics. Sets every element to 3.14 and 2.71, respectively.
		for (auto el : array) {
			el = 3.14;
			std::cout << el << "/";
		}
		std::cout << '\n';
		for (auto el : array2) {
			el = 2.71;
			std::cout << el << "/";
		}
		};

	fun3();
	if (data2.empty() || data3.empty()) {  // arrays should be empty
		std::cout << "\nDouble arrays have no elements, OK\n";
	}
	else {
		std::cout << "\n Ouch!\n";
		for (std::size_t i = 0; i < data2.size(); ++i) {
			std::cout << data2[i] << "^";
		}
		for (std::size_t i = 0; i < data3.size(); ++i) {
			std::cout << data3[i] << "^";
		}
	}
	return 0;
};

int main() {
	ex_a();
	ex_b();
	ex_c();

	return 0;
};