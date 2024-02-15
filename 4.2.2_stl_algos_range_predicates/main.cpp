// we take a look at a few range predicates: sorted, partially sored, partitioned, find partition point
// Tobias Bilgeri, 04.01.2024
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>

using f32_t = float;
using Vector = std::vector<f32_t>;

struct StopWatch {
	std::chrono::high_resolution_clock::time_point _start;
	std::chrono::high_resolution_clock::time_point _end;
	long long _duration_us;

	void start() {
		_start = std::chrono::high_resolution_clock::now();
	}
	void end() {
		_end = std::chrono::high_resolution_clock::now();
	}
	void print_duration() {
		_duration_us = (_end - _start).count() / 1000;
		std::cout << "Elapsed time (us): " << _duration_us << "\n";
	}
};


int main() {
	using namespace std::ranges;
	StopWatch sw{};

	Vector vec8{ 1.0, 2.0, 3.0, -4.0, 10.0 };

	// Find last index (exclusive) until which the elements are sorted.
	sw.start();
	auto pos = is_sorted_until(vec8.begin(), vec8.end()); 
	std::cout << "Vector is sorted up to idx (exclusive): " << *pos << std::endl;
	sw.end();
	sw.print_duration();

	// Check if the complete vector is sorted.
	sw.start();
	bool isSorted = is_sorted(vec8.begin(), vec8.end());
	std::cout << "Vector is sorted? " << (isSorted ? "Yes" : "No") << std::endl;
	sw.end();
	sw.print_duration();

	// Check if the vector is partitioned according to a certain condition.
	sw.start();
	bool isPartitioned = is_partitioned(vec8.begin(), vec8.end(), [](double val) { return abs(val) <= 3.5; });
	std::cout << "Is the vector partitioned with condition |x| <= 3.5? " << (isPartitioned ? "Yes" : "No") << std::endl;
	sw.end();
	sw.print_duration();

	// Find the partition point == 1st point that does not satisfy the condition.
	sw.start();
	auto partitionPoint = partition_point(vec8.begin(), vec8.end(), [](double val) { return val < 0; });
	std::cout << "The partition point has value: " << *partitionPoint << std::endl;
	sw.end();
	sw.print_duration();

	return 0;
}