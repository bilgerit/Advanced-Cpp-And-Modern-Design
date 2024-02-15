// Simple helper file containing utility needed for this exercise.
// We use a C++98 style approach to create templated types, and later on alias templating (C++11 style) to achieve the same goal.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>

// C++ 98 approach // Data storage types
template <typename T>
struct Storage {
	// Possible ADTs and their memory allocators
	// typedef std::vector<T, CustomAllocator<T>> type;
	// typedef std::vector<T, std::allocator<T>> type;
	typedef std::list<T, std::allocator<T>> type;

	// note: std::allocator<T> is the default allocator used to allocate heap memory for the container.
};

template <typename T>
class Client {
	// An example of Composition
private:
	typename Storage<T>::type data; // typename mandatory
public:
	Client(int n, const T& val) : data(n, val) {}
	void print() const {
		std::for_each(
			data.begin(),
			data.end(),
			[](const T& n) { std::cout << n << ","; }
		);
		std::cout << '\n';
	}
	typename Storage<T>::type getData() {
		return data;
	}
};

template <typename T>
using Storage_t = std::list<T, std::allocator<T>>; // C++ 11 approach

template <typename T>
class AliasTemplateClient {
private:
	Storage_t<T> data;
public:
	AliasTemplateClient(int n, const T& val) : data(n, val) {};
	void print() const {
		std::for_each(
			data.begin(),
			data.end(),
			[](const T& n) { std::cout << n << ","; }
		);
		std::cout << '\n';
	}
	Storage_t<T> getData() {
		return data;
	}
};
