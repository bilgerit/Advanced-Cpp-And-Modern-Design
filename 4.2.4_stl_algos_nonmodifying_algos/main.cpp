// In this exercise, we solve some leet-code style problems of finding frequencies,
// subsequences, elements, etc., in vectors.
// We employ a mix of STL and hand-crafted methods, and compare various approaches to 
// achieve the same goals.
// Tobias Bilgeri, 05.01.2024
#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include <numeric>
#include <optional>
#include <functional>
#include <cassert>

// Some printing macros.
#define EXERCISE_HEADER(x) std::cout << "\n\nExercise " << x << "\n\n";
#define PRINT(x) std::cout << x << "\n";
#define PRINT_1D_CONTAINER(x) for(const auto& el: x) { std::cout << el << " ";}; std::cout << "\n";
#define PRINT_MAP(x) for (const auto& [k, v]: x) { std::cout << k << ": " << v << "\n"; };


// Exercise a: function implementation
template<typename T>
std::map<T, uint32_t> calcFrequencies(const std::vector<T>& v) {
	// find element frequencies in a vector by employing an ordered map.
	std::map<T, uint32_t> frequencies;
	for (const T& el : v) {
		frequencies[el] += 1;
	}
	return frequencies;
}

// Exercise b: function implementation
template<typename T>
using DescriptiveStats = std::tuple<T, T, T, T>;

template<typename T>
DescriptiveStats<T> calcDescriptiveStats(const std::vector<T>& v) {
	// calc descriptive stats (sum, avg, max, min) on a vector
	T sum = std::reduce(v.begin(), v.end());
	T avg = sum / v.size();
	T max = *std::max_element(v.begin(), v.end());
	T min = *std::min_element(v.begin(), v.end());
	return DescriptiveStats<T>(sum, avg, max, min);
};



int main() {


	// a. find frequencies
	EXERCISE_HEADER("a. frequencies.");

	std::vector<int> v = { 1, 2, 2, 3, 3, 3, 4, 4, 5 };
	PRINT("ex. a. find frequencies in a vector. input vector: ");
	PRINT_1D_CONTAINER(v);

	auto frequencies = calcFrequencies(v);
	PRINT_MAP(frequencies);



	// b. compute descriptive stats
	EXERCISE_HEADER("b. descriptive stats.");

	auto stats = calcDescriptiveStats(v);
	PRINT(
		"sum=" << std::get<0>(stats)
		<< ", avg=" << std::get<1>(stats)
		<< ", max=" << std::get<2>(stats)
		<< ", min=" << std::get<3>(stats)
	);



	// c. find 1st occurence of 5, then find 1st even number on S using 
	//     (i) std::bind(), (ii) lambda expression.
	//     Note that std::bind2nd is deprecated.
	{
		EXERCISE_HEADER("c");
		std::vector<int> S = { 1,2,-3,4,5,5,5,6 };
		PRINT_1D_CONTAINER(S);

		auto ans1 = std::distance(
			S.begin(),
			std::ranges::find(S.begin(), S.end(), 5)
		);
		PRINT("1st occurence of 5: " << ans1);

		// use bind
		auto check_mod_2 = std::bind(std::modulus<int>(), std::placeholders::_1, 2);
		auto check_is_even = std::bind(std::equal_to<int>(), check_mod_2, 0);
		auto it3 = std::find_if(S.begin(), S.end(), check_is_even);
		auto ans3 = std::distance(S.begin(), it3);

		// use lambda
		auto it4 = std::find_if(S.begin(), S.end(), [](const auto& el) { return el % 2 == 0; });
		auto ans4 = std::distance(S.begin(), it4);

		assert(ans3 == ans4);
	}


	// d. find subsequences
	{
		EXERCISE_HEADER("d");

		std::vector<int> S = { 1,2,5,5,-3,4,5,5,5,6,3,4,5 };
		PRINT_1D_CONTAINER(S);

		// Return the position of the first three consecutive elements having the value 5.
		auto it = std::search_n(S.begin(), S.end(), 3, 5);
		size_t ans = std::distance(S.begin(), it);
		PRINT("Index where first 3 consecutive equal elements occur: " << ans);

		// Return the position of the first element of the first subrange matching {3,4,5}.
		std::vector<int> Sub = { 3, 4, 5 };
		auto it2 = std::search(S.begin(), S.end(), Sub.begin(), Sub.end());
		size_t ans2 = std::distance(S.begin(), it2);
		PRINT("First occurence of the subsequence: " << ans2);

		// Return the position of the first element of the last subrange matching {3,4,5}.
		auto it3 = S.begin();
		std::vector<int>::iterator ans3_it;
		while (it3 != S.end()) {
			ans3_it = it3;
			it3 = std::search(it3 + 1, S.end(), Sub.begin(), Sub.end());
		}
		size_t ans3 = std::distance(S.begin(), ans3_it);
		PRINT("Last occurence of the subsequence: " << ans3);

	}



	// e. find the first element in S that has value equal to the value of the
	//    following element.
	{
		EXERCISE_HEADER("e");
		std::vector<int> S = { 1, 2, 5, 5, -3, 4, 5, 5, 5, 6, 3, 4, 5 };
		PRINT_1D_CONTAINER(S);

		// check if condition is met anywhere.
		// (alternatively: use std::adjacent_find)
		std::optional<int> ans;
		for (auto it = S.begin(); it != S.end(); it++) {
			if (*it == *(it + 1)) {
				ans = *it;
				break;
			}
		}
		if (!ans) {
			PRINT("No equal subsequent values found.");
		}
		else {
			PRINT("First value for which we found two subsequent equal values: " << ans.value());
		}
	}



	// f. check if elements of 2 containers are equal.
	//    Not sure how this is meant TBH. std::equal on vects of unequal size can lead
	//    to undefined behaviour. I could catch this but this is obviously a trivial exercise.
	//    Using std::includes instead.
	{
		EXERCISE_HEADER("f");

		std::vector<int> S = { 1, 2, 5, 5, -3, 4, 5, 5, 5, 6, 3, 4, 5 };
		std::vector<int> S1 = { 1,2,5 };

		bool ans = std::ranges::includes(S.begin(), S.end(), S1.begin(), S1.end());
		PRINT("Is S1 included in S? " << std::boolalpha << ans);
	}

	return 0;
}