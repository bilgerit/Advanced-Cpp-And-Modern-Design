// In this exercise, we compare different ways to provide callables to stl algos.
// Result (in short): Try using lambdas (at least for this use case).
// Tobias Bilgeri, 05.01.2024
#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <chrono>

#define PRINT_CONTAINER(container) for (const auto& el: container) { std::cout << el << " ";};
#define PRINT(statement) std::cout << statement;

/*
* exercise a  
* 
* User defined function objects: 
* Often very clear, familiar intuitive to whoever 
* implemented them, but less so for others. One big issue is that they will be defined
* _somewhere_ in the code, but not exactly where they are used, and hence require 
* additional effort by any reader of the code in tracking down where things come from.
* 
* STL algos:
* Very clear for people familiar with STL's vast range of algos.
* Personally, I find them easy to read, but since I don't get to use them very often,
* I don't remember most of them, or don't remember the precise syntax, and just end up 
* writing for-loops and lambdas (or similar) instead.
* 
* Lambda functions:
* Often defined in-place and it is much easier to read than traditional function objects.
*/


// exercise b -- perform opereration on container using 
// (1) custom callable obj 
// (2) obj derived from std::unary_function
// (3) lambda


template <typename T, T threshold>
struct GreaterThan {
	// Check if an element is greater than threshold.
	bool operator () (const T& val) const {
		return std::abs(val) > threshold;
	}
};

// std::unary_function GOT REMOVED IN C++17
/*
template <typename T, T threshold>
struct GreaterThanSTL : std::unary_function<int, bool> {
	// Check if an element is greater than threshold.
	// Derived from std::unary_function<int, bool>.
	bool operator () (const T& val) const {
		return std::abs(val) > threshold;
	}
};
*/


class StopWatch {
	// Simple Stop Watch.
private:
	std::chrono::high_resolution_clock::time_point _start;
	std::chrono::high_resolution_clock::time_point _end;
public:
	void start() {
		_start = std::chrono::high_resolution_clock::now();
	}
	void stop() {
		_end = std::chrono::high_resolution_clock::now();
	}
	long long duration_ns() {
		return (_end - _start).count();
	}
};


int main() {

	std::vector<int> v = { 1,2,1,4,5,5,-1 };
	const int thresh = 2;
	StopWatch sw{};


	// Callable object
	GreaterThan<int, thresh> obj_greater_than = {};
	std::set<int> ans1 = {};

	sw.start();
	std::ranges::copy_if(v.begin(), v.end(), std::inserter(ans1, ans1.begin()), obj_greater_than);
	sw.stop();

	PRINT("\nResult -- callable obj: ")
	PRINT_CONTAINER(ans1)
	PRINT(", Duration (ns): " << sw.duration_ns());


	// STL algo
	// callable: dropping the abs for some dummy implementation using bind ... since std::unary_function is not available. 
	auto GreaterThanSTL = std::bind(std::greater<>(), std::placeholders::_1, thresh);
	std::set<int> ans2 = {};

	sw.start();
	std::ranges::copy_if(v.begin(), v.end(), std::inserter(ans2, ans2.begin()), GreaterThanSTL);
	sw.stop();

	PRINT("\nResult -- stl algo: ")
	PRINT_CONTAINER(ans2)
	PRINT(", Duration (ns): " << sw.duration_ns());


	// Lambda
	std::set<int> ans3 = {};

	sw.start();
	std::ranges::copy_if(v.begin(), v.end(), std::inserter(ans3, ans3.begin()), [](const int& x) { return std::abs(x) > thresh; });
	sw.stop();

	PRINT("\nResult -- lambda: ")
	PRINT_CONTAINER(ans2)
	PRINT(", Duration (ns): " << sw.duration_ns())


	// Efficiency: Lambda (best) > bind > struct (worst)
	// Readability: Lambda is obviously the most readable solution
	// Maintainability: Lambda is again the best solution, since it is only used in-place.
	//                  Any change to the lambda won't influence any other code (with the 
	//                  obvious exception that the results will be different).

	return 0;
}