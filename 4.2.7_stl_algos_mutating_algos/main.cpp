//  Mutating algorithms
// Tobias Bilgeri, 06.01.2024
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

template<typename Container>
void print_container(const Container& c) {
	// print a compound type such as vector or array.
	static_assert(std::is_compound_v<Container>, "Container must be a compound type!");
	for (const auto& el : c) {
		std::cout << el << " "; 
	} 
	std::cout << std::endl;
}


using PowerSet = std::vector<std::vector<int>>;

PowerSet calc_power_set(const std::vector<int>& S) {
	// start w/ one empty set
	PowerSet result(1);

	// copy create a copy of the current state of the power set, append the current element
	// to it, and add it to the power set.
	for (int i : S) {
		PowerSet temp = result;

		for (std::vector<int>& subset : temp) {
			subset.push_back(i);
		}

		result.insert(result.end(), temp.begin(), temp.end());
	}

	return result;
}


int main() {

	// a. reverse copy

	std::vector<int> S = { 1, -1, 7, 8, 9, 10 };
	std::vector<int> S2;
	std::reverse_copy(S.cbegin(), S.cend(), std::inserter(S2, S2.end()));

	print_container(S);
	print_container(S2);



	// b. rotate:
	// find occurence of 8 and rotate vector s.t. 8 is now at the front.

	auto it = std::find(S.begin(), S.end(), 8);
	std::rotate(S.begin(), it, S.end());
	print_container(S);



	// c. power set
	auto power_set = calc_power_set(S);
	for (const auto& el : power_set) {
		print_container(el);
	}



	// d. move elements from one vector to frond of another vector.
	// in contrast to exercise b, we move only a specific subset of elements to the front.

	std::vector<int> subset = { 8, 9, 10 };
	auto itd = std::search(S.begin(), S.end(), subset.begin(), subset.end());
	std::rotate(S.begin(), it, it + subset.size());
	print_container(S);

	return 0;
}