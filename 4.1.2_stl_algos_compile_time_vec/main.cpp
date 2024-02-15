// In this exercise, we create a compile-time vector.
// 'Vector' herein stands for a mathematical vector, not and 'extensible array'.
// Tobias Bilgeri, 05.01.2024
#include "Vector.h"
#include <iostream>
#include <sstream>

template<typename T, size_t N>
void print_vec(const Vector<T, N>& v) {
    std::stringstream ss;
    ss << "[";
    for (auto it = v.begin(); it != v.end(); ++it) {
        ss << *it;
        if (it + 1 != v.end()) {
            ss << ",";
        }
    }
    ss << "]";
    std::cout << ss.str() << std::endl;
}


int main() {
	Vector<int16_t, 3> v1 { 1, 1, 1 };
	Vector<int16_t, 3> v2 { 2, 2, 2 };
	print_vec(v1);
	print_vec(v2);

	// Arithmetics
	print_vec(v1 + v2);
	print_vec(v1 - v2);
	print_vec(v1.hadamard(v2));
	std::cout << v1.dot(v2) << std::endl;

	print_vec(v1 * 2);  // overloaded operator
	print_vec(2 * v1);  // friend function
	v1.modify([](auto el) { return el * 2; });  // function object arg
	print_vec(v1);

	auto v3 = v1;
	print_vec(v3);
	auto v4 = std::move(v1);  // performs member-wise move, which is a copy for built-in types usually.
	print_vec(v4);

	return 0;
}