// Simple helper file containing utility needed for this exercise.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <initializer_list>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


template<typename T>
class SimpleClass {
	// Dummy class which supports different ways of initilization.
private:
	T m_int;
	vector<T> m_v;
public:
	SimpleClass() = default;
	SimpleClass(const T& i, const vector<T>& v): m_int(i), m_v(v) {}
	SimpleClass(const T& i, const initializer_list<T>& il) : m_int(i), m_v(il) {}
	SimpleClass(const SimpleClass& sc) : m_int(sc.m_int), m_v(sc.m_v) {}
	SimpleClass(SimpleClass&& sc) : m_int(move(sc.m_int)), m_v(move(sc.m_v)) {}

	void print() const {
		cout << "SimpleClass: m_int=" << m_int << ", m_v=[";
		for (auto& e : m_v) {
			cout << e << ", ";
		}
		cout << "]" << endl;
	}
};


struct S
{
	// Dummy struct which supports different ways of initilization.
	int x;
	struct Foo {int i; int j; int a[3];	} b;

	void print() {
		cout << "S: x=" << x << ", b.i=" << b.i << ", b.j=" << b.j << ", b.a=[";
		std::for_each(
			std::begin(b.a), 
			std::end(b.a), 
			[](int& e) { cout << e << ", "; }
		);
		cout << "]" << endl;
	}
};