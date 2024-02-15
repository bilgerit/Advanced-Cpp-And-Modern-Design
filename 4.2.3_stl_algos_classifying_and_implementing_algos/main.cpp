// In this exercise, we take a look at various STL algorithms acting on containers,
// classify their behaviour, and implement some examples.
// Tobias Bilgeri, 04.01.2024
#pragma once
#define PRINT(txt) std::cout << "\n" << txt << "\n";
#define PRINT_CONTAINER(container) for (auto i : container) { std::cout << i << " "; } std::cout << "\n";
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

/*
STL algorithm categories:
- C1: Nonmodifying.
- C2: Modifying. (alter some values)
- C3: Removing.
- C4: Mutating.  (move some values around)
- C5: Sorting.
- C6: Sorted-Range.
- C7: Numeric.   (imported via <numeric> rather than <algorithm>)

Consider a general sequence container for example, std::list. 
To which categories do the following algorithms belong and which specific algorithm
would you use in each case?

a) Scale all values by a given factor. 
		C2
		transform
b) Count the number of elements whose values are in a given range. 
		C1
		count_if
c) Find the average, minimum and maximum values in a container. 
		C1, c7
		accumulate, max_element, min_elment
d) Find the first element that is (that is not) in a range. 
		C1
		find, find_if_not
e) Search for all occurrences of ‘3456’ in the container. 
		C1
		find
f) Determine if the elements in two ranges are equal. 
		C1
		equal
g) Determine if a set is some permutation of ‘12345’. 
		C1
		is_permutation
h) Is a container already sorted? 
		C6
		is_sorted
i) Copy a container into another container.
		C2
		copy
j) Move the last 10 elements of a container to the front.
		C4
		rotate
k) Swap two ranges at a given position. 
		C2
		swap_ranges
l) Generate values in a container based on some formula.
		C2
		generate
m) Replace all uneven numbers by zero. 
		C2
		replace_if
n) Remove all elements whose value is less than 100. 
		C3
		remove_if
o) Shuffle a container randomly (pre- and post-C++11 versions). 
		C4
		random_shuffle, shuffle
p) Compute one-sided divided differences of the values in a container. 
		C7
		adjacent_difference


Note: return values of algorithms can be:
	- iterator
	- container::value_type
	- bool
	- void
	...
*/


int main() {
	std::vector<int> v1 = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };
	std::vector<int> v2 = { 5, 4, 3, 2, 1 };
	std::vector<int> v3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 3, 4, 5, 6, 7 };
	std::vector<int> v4 = { 3, 4, 5, 6, };
	std::vector<int> v5 = { 1, 2, 3, 4, 5 };

	PRINT("input vectors");
	PRINT_CONTAINER(v1);
	PRINT_CONTAINER(v2);
	PRINT_CONTAINER(v3);
	PRINT_CONTAINER(v4);
	PRINT_CONTAINER(v5);

	// scale
	std::ranges::transform(v1.begin(), v1.end(), v1.begin(), [](int i) { return i * 2; });
	std::ranges::transform(v2.begin(), v2.end(), v2.begin(), [](int i) { return i * 2; });
	PRINT("vector 1: after scale by 2: ");
	PRINT_CONTAINER(v1);

	// count
	int count = std::ranges::count_if(v1.begin(), v1.end(), [](int i) { return i > 5.1; });
	PRINT("vector 1: count of elements > 5.1: " << count);
	
	// avg, min, max
	// min, max have output type iterator!
	int avg = std::accumulate(v1.begin(), v1.end(), 0) / v1.size();
	int min = *std::ranges::min_element(v1.begin(), v1.end());
	int max = *std::ranges::max_element(v1.begin(), v1.end());
	PRINT("vector 1: avg: " << avg << " min: " << min << " max: " << max);

	// find, find_if_not
	// output type is iterator
	auto it = std::ranges::find(v1.begin(), v1.end(), 4);
	auto it2 = std::ranges::find_if_not(v1.begin(), v1.end(), [](int i) { return i > 4; });
	auto idx = std::distance(v1.begin(), it);
	auto idx2 = std::distance(v1.begin(), it2);
	PRINT("vector 1: find 4 at index: " << idx);
	PRINT("vector 1: find_if_not > 4 at index: " << idx2);

	// find all occurence of '3456'
	// use loop to find ALL occurences
	// return type is iterator, for each sequence found
	auto its = v3.begin();
	while (its != v3.end()) {
		its = std::search(its, v3.end(), v4.begin(), v4.end());
		if (its != v3.end()) {
			PRINT("vector 3: found 3456 at index: " << std::distance(v3.begin(), its));
			its += 1;
		}
	}
	
	// determine if two ranges are equal
	bool equal = std::ranges::equal(v1.begin(), v1.end(), v2.begin(), v2.end());
	PRINT("vector 1 and 2 are equal: " << equal);

	// determine if a set is some permutation of '12345'
	bool permutation = std::ranges::is_permutation(v3.begin(), v3.end(), v5.begin(), v5.end());
	PRINT("vector 3 and 5 are permutation: " << permutation);

	// is a container already sorted
	bool sorted1 = std::ranges::is_sorted(v1.begin(), v1.end());
	bool sorted5 = std::ranges::is_sorted(v5.begin(), v5.end());
	PRINT("vector 1 is sorted: " << sorted1);
	PRINT("vector 5 is sorted: " << sorted5);

	// copy a container into another container
	// no return value!
	// use std::back_inserter to make vector grow if needed!
	std::copy(v2.begin(), v2.end(), std::back_inserter(v5));
	PRINT("vector 2 after copying it into vector 5 (via backinsertion): ");
	PRINT_CONTAINER(v5);

	// move the last 10 elements of a container to the front
	std::rotate(v3.begin(), v3.end() - 2, v3.end());
	PRINT("vector 3 after rotating last 2 elements to the front: ");
	PRINT_CONTAINER(v3);

	// swap two ranges at a given position
	std::swap_ranges(v3.begin(), v3.begin() + 3, v3.begin() + 3);
	PRINT("vector 3 after swapping first 3 elements with second 3 elements: ");
	PRINT_CONTAINER(v3);

	// generate values in a container based on some formula
	std::ranges::generate(v3.begin(), v3.end(), [n = 0]() mutable { return n++; });
	PRINT("vector 3 after generating values based on formula: ");
	PRINT_CONTAINER(v3);

	// replace all uneven numbers by zero
	std::ranges::replace_if(v3.begin(), v3.end(), [](int i) { return i % 2 != 0; }, 0);
	PRINT("vector 3 after replacing all uneven numbers by zero: ");
	PRINT_CONTAINER(v3);

	// remove all elements whose value is less than 100
	// return value is iterator to the end of the new container
	// Note: std::remove_if behaves differently from std::ranges::remove_if.
	auto ite = std::remove_if(v3.begin(), v3.end(), [](int i) { return i < 100; });
	v3.erase(ite, v3.end());
	PRINT("vector 3 after removing all elements whose value is less than 100: ");
	PRINT_CONTAINER(v3);

	// shuffle a container randomly
	std::mt19937 rgen(42);
	std::shuffle(v4.begin(), v4.end(), rgen);
	PRINT("vector 4 after shuffling randomly: ");
	PRINT_CONTAINER(v4);

	// compute one-sided divided differences of the values in a container
	std::vector<int> v6;
	std::adjacent_difference(v4.begin(), v4.end(), std::back_inserter(v6));
	PRINT("vector 6 after computing one-sided divided differences of the values in vector 4: ");
	PRINT_CONTAINER(v6);

	return 0;
}