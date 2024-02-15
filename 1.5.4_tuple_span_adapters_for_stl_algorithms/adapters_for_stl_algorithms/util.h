// Simple helper file containing utility needed for this exercise.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <vector>
#include <tuple>
#include <algorithm>
#include <memory>
#include <string>
#include <cmath>
#include <functional>
#include <sstream>



template<typename Container>
std::string container_to_string(const Container& c) {
	// Print a container element by element.
	std::stringstream ss;
	ss << "[";
	for (auto& x : c) {
		ss << x << ", ";
	}
	ss << "]";
	return ss.str();
}


template<typename Container, typename ContainerPointer>
int adapter_container_pointer_to_index(const Container& c, const ContainerPointer& p_c) {
	// Adapter mapping container pointers to an index via std algo std::distance.
	return std::distance(c.begin(), p_c);
}


template<typename Container>
auto adapter_container_index_to_pointer(const Container& c, const int& i) {
	// Adapter mapping an index to a container pointer.
	// Trivial function but let's keep it for the sake of this exercise.
	return c.begin() + i;
}


template<typename Container, typename T>
int ex_a_find_idx_of_first_element(const Container& c, const T& x) {
	// Find index of first element in container c for which vec[i] <= x < vec[i+1].
	// To force usage of the adapter, we decide to loop through the container using pointers, and then convert the pointers to an integer subsequently.
	// (in practice, we could just loop through the container using integer indices, but this is just for demonstration purposes)
	int ans = -1;
	for (auto p_c = c.begin(); p_c != c.end(); p_c++) {
		if (*p_c <= x && x < *(p_c + 1)) {
			ans = adapter_container_pointer_to_index(c, p_c);
			return ans;
		}
	}
	return ans;
}


template<typename Container, typename T>
class FindMaxErrorInRange {
	// Find the maximum error between two containers in a given range.
	// Error types: abosulte, relative.
private:
	std::string m_ABSOLUTE_ERROR{ "ABSOLUTE_ERROR" };
	std::string m_RELATIVE_ERROR{ "RELATIVE_ERROR" };
	std::string m_error_metric;
	std::function<T(typename Container::iterator, typename Container::iterator)> m_error_function;  // function handling computation of a point-wise error.

public:
	FindMaxErrorInRange() { m_error_metric = m_ABSOLUTE_ERROR; }

	explicit FindMaxErrorInRange(const std::string& error_metric): m_error_metric(error_metric) {
		if (error_metric == m_ABSOLUTE_ERROR) {
			// Note the use of 'typename' herein. See https://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords
			// In order to be able to make use of the subtype, we need to hint that Container::iterator is based on a templated type.
			m_error_function = [](typename Container::iterator p_c, typename Container::iterator p_d) { return std::abs(*p_c - *p_d); };
		} else if (error_metric == m_RELATIVE_ERROR) {
			m_error_function = [](typename Container::iterator p_c, typename Container::iterator p_d) { return std::abs(*p_c - *p_d) / std::abs(*p_d); };
		}
		else {
			throw std::invalid_argument("FindMaxErrorInRange: Error when calling constructor. <error_metric> must be either ABSOLUTE_ERROR or RELATIVE_ERROR");
		}
	}

	auto operator() (Container& c, Container& d, const int& i, const int&j) {
		typename Container::iterator p_c = c.begin() + i;
		typename Container::iterator p_d = d.begin() + i;

		T max_error{ 0 };
		int max_error_index{ -1 };
		T error;
		for (int k = i; k <= j; k++) {
			error = m_error_function(p_c, p_d);
			if (error > max_error) {
				max_error = error;
				max_error_index = k;
			}
			p_c += 1;
			p_d += 1;
		}
		return std::make_tuple(max_error, max_error_index);
	}
};
