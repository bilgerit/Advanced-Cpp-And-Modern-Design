// Simple header file containing utility needed for this exercise.
//   - Verbose dummy class w/ various constructors
//   - Utility for printing vectors.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;


template <typename T>
string constexpr vec_to_string(const vector<T>& v) {
	string vector_string = "[";
	for (size_t i = 0; i < v.size(); ++i) {
		vector_string += to_string(v[i]);
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
	// Dummy class for demonstrating move semantics and different constructors.
private:
	vector<T> v;

public:
	constexpr C() = default;
	explicit constexpr C(C&& c) : v(move(c.v)) { cout << "move constructor called" << endl; };
	explicit constexpr C(const C& c) : v(c.v) { cout << "copy constructor called" << endl; };
	void constexpr operator = (C& c) {
		cout << "assignment operator called" << endl;
		this->v = c.v;
	};
	~C() { cout << "default destructor called" << endl; };
	explicit constexpr C(const vector<T> &V) : v(V) { cout << "constructor with vector input called" << endl; };
	explicit constexpr C(vector<T>&& V) : v(move(V)) { cout << "move constructor with vector input called" << endl; };

	void constexpr print_members() const {
		cout << "printing members of class C with reference " << this << ": ";
		cout << vec_to_string<T>(this->v) << endl;
	}

	void constexpr scale(const T& c) {
		cout << "scaling method called for class C with reference " << this << " with multiplier " << c << endl;
		for (size_t i = 0; i < this->v.size(); ++i) {
			this->v[i] *= c;
		}
	}
};
