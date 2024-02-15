// In this exercise, take a look at some std::ranges algorithms for finding 
// elements in containers that satisfy some condition.
// Tobias Bilgeri, 05.01.2024
#pragma once
#include <iostream>
#include <tuple>
#include <functional>
#include <algorithm>
#include <vector>
#include <cassert>

# define EXERCISE_HEADER(x) std::cout << "\n\n" << x << "\n\n" << std::endl;

using namespace std;

using Range = tuple<size_t, size_t>;
using Result = tuple<Range, bool>;
using Result1 = tuple<size_t, bool>;

template<typename _Elem> using UnaryBoolFn = function<bool(_Elem)>;

using Vector = vector<int>;
using value_type = Vector::value_type;


// a
Result find_sequential_greater(const Vector& v, value_type x){
	// find indices of first 2 elements for which the 2nd is larger than the first.
	for (size_t j = 0; j < v.size() - 1; ++j)
	{
		if (v[j] <= x && v[j + 1] > x)
		{
			return make_tuple(std::make_tuple(j, j + 1), true);
		}
	} 
	return make_tuple(std::make_tuple(999, 999), false);
}

Result1 find_first(const Vector& v, const UnaryBoolFn<value_type>& F) {
	// find-first wrapper.
	auto it = find_if(v.begin(), v.end(), F);
	if (it == v.end()) return make_tuple(0, false);
	size_t idx = distance(v.begin(), it);
	return make_tuple(idx, true);
}

Result1 find_if_greater(const Vector& v, value_type x) {
	// find first element largern than x.
	UnaryBoolFn comp = [&x](const value_type& el) { return el > x; };
	return find_first(v, comp);
}

Result1 find_if_equals(const Vector& v, value_type x) {
	// find first element equals x.
	UnaryBoolFn comp = [&x](const value_type& el) { return el == x; };
	return find_first(v, comp);
}


// b
Result1 lower_bound_index(const Vector& v, value_type x) {
	// first idx for which element >= x.
	auto it = lower_bound(v.begin(), v.end(), x);
	if (it == v.end()) return make_tuple(0, false);
	size_t idx = distance(v.begin(), it);
	return make_tuple(idx, true);
}

Result1 upper_bound_index(const Vector& v, value_type x) {
	auto it = upper_bound(v.begin(), v.end(), x);
	// first idx for which element < x.
	if (it == v.end()) return make_tuple(0, false);
	size_t idx = distance(v.begin(), it);
	return make_tuple(idx, true);
}


// c
Range equal_range_indexes(const Vector& v, value_type x) {
	// range [start, end[ of equal values.
	auto pair = equal_range(v.begin(), v.end(), x);
	return make_tuple(distance(v.begin(), pair.first), distance(v.begin(), pair.second));
}


int main() {
	EXERCISE_HEADER("exercise a")
	{
		// some tests
		Vector v = { 1, 2, 3, 4, 5 };
		value_type x = 2;
		Result res = find_sequential_greater(v, x);
		assert(get<1>(res) == true);
		assert(get<0>(get<0>(res)) == 1);
		assert(get<1>(get<0>(res)) == 2);
	}

	EXERCISE_HEADER("exercise b")
	{
		// some tests
		Vector v = { 1, 2, 3, 4, 5 };
		value_type x = 3;
		Result1 res1 = lower_bound_index(v, x);
		Result1 res2 = upper_bound_index(v, x);
		assert(get<1>(res1) == true);
		assert(get<0>(res1) == 2);
		assert(get<1>(res2) == true);
		assert(get<0>(res2) == 3);
	}

	EXERCISE_HEADER("exercise c")
	{
		// some tests
		Vector v = { 1, 2, 3, 3, 3, 4, 5 };
		value_type x = 3;
		Range res = equal_range_indexes(v, x);
		assert(get<0>(res) == 2);
		assert(get<1>(res) == 5);
	}

	EXERCISE_HEADER("exercise d")
	{
		Vector v = { 1, 2, 3, 4, 5 };
		auto it = find_if_not(v.begin(), v.end(), [](value_type val) { return val < 3; });
		cout << "First value not less than 3: " << *it << ", at index: " << distance(v.begin(), it) << endl;
	}

	return 0;
}