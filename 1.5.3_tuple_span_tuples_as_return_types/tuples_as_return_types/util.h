// Simple helper file wherein we define functions to compute statistics on containers.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <vector>
#include <tuple>
#include <boost/numeric/ublas/vector.hpp>
#include <cmath>
#include <numeric>
#include <unordered_map>


template<typename T>
using UBLASVector = boost::numeric::ublas::vector<T>;

template<typename T>
using STLVector = std::vector<T>;


template<typename Container, typename T>
std::tuple<T, T, T, T, T> calc_summary_stats(const Container& c) {
	// Compute summary statistics on some container with elements of type T.
	/*
	Accumulators and minmax_element don't work with ublas. Too bad!
	Basic iterator-based loops also don't work. Will access elments via index instead, as this finally works with both UBLAS and STL vectors.
	*/
	T mean{ 0 };
	T mean_dev{ 0 };
	T max{ c[0] };
	T min{ c[0] };
	T range;
	T std_dev;
	T var{ 0 };

	
	//The followingn works for STL vectors only (as it uses pointers like c.begin()):
	//
	//mean = std::accumulate(c.begin(), c.end(), 0.0) / c.size();
	//mean_dev = std::accumulate(c.begin(), c.end(), 0.0, [&mean](T sum, T& val) {return sum + std::abs(val - mean); }) / c.size();
	//var = std::accumulate(c.begin(), c.end(), 0.0, [&mean](T sum, T& val) {return sum + std::pow(val - mean, 2); }) / (c.size() - 1);
	//std_dev = std::sqrt(var);
	//auto [min, max] = std::ranges::minmax_element(c.begin(), c.end());
	//range = *max - *min;

	

	for (int i = 0; i != c.size(); i++) {
		mean += c[i];
	}
	mean /= c.size();

	for (int i = 0; i != c.size(); i++) {
		mean_dev += std::abs(c[i] - mean);
		var += std::pow(c[i] - mean, 2);
	}
	mean_dev /= c.size();
	var /= (c.size() - 1);
	std_dev = std::sqrt(var);
	
	for (int i = 1; i != c.size(); i++) {
		if (c[i] > max) {
			max = c[i];
		}
		if (c[i] < min) {
			min = c[i];
		}
	}
	range = max - min;

	return std::make_tuple(mean, mean_dev, range, std_dev, var);
}

template<typename Container, typename T>
T calc_median_of_sorted_container(const Container& c) {
	// Compute the median of a sorted array.
	if (c.size() % 2 == 1) {
		return c[c.size() / 2];
	}
	else {
		return (c[c.size() / 2] + c[c.size() / 2 - 1]) / 2;
	}
}

template<typename Container, typename T>
T calc_mode(const Container& c) {
	// Compute the mode by counting elements within an unordered map, and then finding the maximum count.
	// Additional logic: if two elements appear equally often, we choose the smaller one.
	std::unordered_map<T, int> counts;
	for (int i = 0; i != c.size(); i++) {
		counts[c[i]]++;
	}
	T mode;
	int max_count{ 0 };
	for (auto& [key, value] : counts) {
		if (value > max_count) {
			max_count = value;
			mode = key;
		}
		else if (value == max_count && key < mode) {
			mode = key;
		}
	}
	return mode;
}
