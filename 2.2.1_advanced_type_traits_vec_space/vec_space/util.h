// Simple helper file containing the free functions needed for this exercise (flexible arithmetic operations on scalars and vectors via bridge-type functions.).
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <type_traits>

template <typename T>
void Print_impl(const T& t, std::true_type) {
	// Print the elements of a container.
	std::cout << "[";
	for (auto& el: t) {
		std::cout << el << ", ";
	}
	std::cout << "]" << std::endl;
}

template <typename T>
void Print_impl(const T& t, std::false_type) {
	// Print a scalar value.
	std::cout << t << std::endl;
}

template <typename T>
void Print(const T& t) {
	// Switchable Bridge for printing an object. Calls wrapped function depending on whether t has a compound type or not.
	Print_impl(t, std::is_compound<T>());
}

// Forward declaration of the switchable bridge for the addition function.
template <typename T> T Addition(const T& t1, const T& t2);

template <typename T>
T Addition_impl(const T& t1, const T& t2, std::true_type) {
	// Vector addition
	// use simple indexing rather than pointers such that it works for boost vectors too.
	T result(t1);
	for (int i = 0; i < t1.size(); ++i) {
		// result[i] = Addition(t1[i], t2[i]);   // using this would allow to handle vecs of compounds
		result[i] = t1[i] + t2[i];
	}
	return result;
}

template <typename T>
T Addition_impl(const T& t1, const T& t2, std::false_type) {
	// Scalar addition
	return t1 + t2;
}

template <typename T>
T Addition(const T& t1, const T& t2) {
	// Addition: Calls wrapped function depending on whether t1 and t2 are of compound type or not.
	return Addition_impl(t1, t2, std::is_compound<T>());
}

// Forward declaration of the switchable bridge for additive inverse function.
template <typename T> T AdditiveInverse(const T& t);

template <typename T>
T AdditiveInverse_impl(const T& t, std::true_type) {
	// Vector space additive inverse
	// use simple indexing rather than pointers such that it works for boost vectors too.
	T result(t);
	for (int i = 0; i < t.size(); i++) {
		// result[i] = AdditiveInverse(t[i]);   // using this would allow to handle vecs of compounts
		result[i] = - t[i];
	}
	return result;
}

template <typename T>
T AdditiveInverse_impl(const T& t, std::false_type) {
	// Scalar additive inverse
	return -t;
}

template <typename T>
T AdditiveInverse(const T& t) {
	// Vector space additive inverse
	return AdditiveInverse_impl(t, std::is_compound<T>());
}

// Forward declaration of the switchable bridge for scalar multiplication function.
template <typename S, typename V> V ScalarMultiplication(const S& s, const V& v);

template <typename S, typename V>
V ScalarMultiplication_impl(const S& s, const V& v, std::true_type) {
	// multiply a vector by a scalar, element-wise.
	V result(v);
	for (int i = 0; i < v.size(); i++) {
		// result[i] = ScalarMultiplication(s, v[i]);   // using this would allow to handle vecs of compounts
		result[i] = s * v[i];
	}
	return result;
}

template <typename S, typename V>
V ScalarMultiplication_impl(const S& s, const V& v, std::false_type) {
	// multiply two scalars.
	return s * v;
}

template <typename S, typename V>
V ScalarMultiplication(const S& s, const V& v) {
	// General Scalar multiplicaiton. Can handle v being of both compount and non-compound type.
	return ScalarMultiplication_impl(s, v, std::is_compound<V>());
}
