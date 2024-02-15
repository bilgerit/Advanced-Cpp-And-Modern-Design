#pragma once
#include <iostream>
#include <stack>
#include <algorithm>


template<typename T>
void println(const T& printable) {
	std::cout << printable << "\n";
}


template <typename T>
struct StackADT {
	// custom stack wrapper which implements the operations described in the exercise.
	std::stack<T> native;

	void max() {
		T a = native.top();
		native.pop();

		T b = native.top(); 
		native.pop();

		native.push(std::max(a, b));
	}

	void min() {
		T a = native.top();
		native.pop();

		T b = native.top();
		native.pop();

		native.push(std::min(a, b));
	}

	void over() {
		if (native.size() < 2) {
			println("Warning: Stack::over called with less than 2 values in the stack. Ignoring this call");
			return;
		}
		T a = native.top();
		native.pop();

		T b = native.top();

		native.push(a);
		native.push(b);
	}

	void rot() {
		if (native.size() < 3) {
			println("Warning: Stack::rot called with less than 2 values in the stack. Ignoring this call");
			return;
		}
		T a = native.top();
		native.pop();

		T b = native.top();
		native.pop();

		T c = native.top();
		native.pop();

		native.push(b);
		native.push(a);
		native.push(c);
	}

	void swap() {
		if (native.size() < 2) {
			println("Warning: Stack::over called with less than 2 values in the stack. Ignoring this call");
			return;
		}
		T a = native.top();
		native.pop();

		T b = native.top();
		native.pop();

		native.push(a);
		native.push(b);
	}

	void drop() {
		native.pop();
	}

	void print() const {
		auto temp = native;
		while (!temp.empty()) {
			std::cout << temp.top() << " ";
			temp.pop();
		}
		std::cout << "\n";
	}
};