// Simple header file containing utility needed for this exercise (mainly the basic and lateron improved classes, plus printing tools).
// The improved class demonstrated some modern ways to write better classes.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <string>
#include <vector>

template <typename T>
std::string constexpr vec_to_string(const std::vector<T>& v) {
	std::string vector_string = "[";
	for (size_t i = 0; i < v.size(); ++i) {
		vector_string += std::to_string(v[i]);
		if (i != v.size() - 1) {
			vector_string += ", ";
		}
	}
	vector_string += "]";
	return vector_string;
}

template <typename T>
class C
{
	// Simple class we will later improve.
private:
	std::vector<T> v;

public:
	C() { std::cout << "default constructor called" << std::endl; };
	~C() { std::cout << "default destructor called" << std::endl; };
	C(const std::vector<T>& V) : v(V) { std::cout << "constructor with vector input called" << std::endl; };
	C(const C& c) : v(c.v) { std::cout << "copy constructor called" << std::endl; };

	void operator = (C& c) {
		std::cout << "assignment operator called" << std::endl;
		this->v = c.v;
	};

	void print_members() const {
		std::cout << "printing members of class C with reference " << this << ": ";
		std::cout << vec_to_string<T>(this->v) << std::endl;
	}

	void scale(const T& c) {
		std::cout << "scaling method called for class C with reference " << this << " with multiplier " << c << std::endl;
		for (size_t i = 0; i < this->v.size(); ++i) {
			this->v[i] *= c;
		}
	}
};

template <typename T>
class CImproved
{
	// Improved class:
	// Use constexpr and noexcept, delete copy constructor and assignment operator, and make constructor explicit.
private:
	std::vector<T> v;
	/*
	// Need to comment this block out:
	// My compiler does not allow for deleting a constructor, and then declaring it again, even if private.
	// (or maybe I missunderstand the question?)

	explicit C(const C& c) : v(c.v) { cout << "copy constructor called" << endl; };

	void operator = (C& c) {
		cout << "assignment operator called" << endl;
		this->v = c.v;
	};
	*/

public:
	constexpr CImproved() = default;
	CImproved(const CImproved& c) = delete;
	void operator = (CImproved& c) = delete;

	~CImproved() { std::cout << "default destructor called" << std::endl; };
	explicit constexpr CImproved(const std::vector<T>& V) : v(V) { std::cout << "constructor with vector input called" << std::endl; };

	void constexpr print_members() const noexcept {
		std::cout << "printing members of class C with reference " << this << ": ";
		std::cout << vec_to_string<T>(this->v) << std::endl;
	}

	void constexpr scale(const T& c) {
		std::cout << "scaling method called for class C with reference " << this << " with multiplier " << c << std::endl;
		for (size_t i = 0; i < this->v.size(); ++i) {
			this->v[i] *= c;
		}
	}
};
