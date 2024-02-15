// Same exercise as before with 'Vector', but this time using a 'Matrix'.
// Matrix is an array of arrays and contains various methods for performing arithmetics.
// Tobias Bilgeri, 05.01.2024
#pragma once
#include "Matrix.h"

int main() {
    // uniform value construction
    Matrix<int16_t, 2, 2> m1(1);
    m1.print();

    // initializer list construction
    Matrix<int16_t, 2, 2> m2{ {2, 2}, {2, 2} };
    m2.print();

    // addition
    auto m3 = m1 + m2;
    m3.print();

    // subtraction
    m3 = m1 - m2;
    m3.print();

    // negation
    m3 = -m1;
    m3.print();

    // multiplication by scalar
    m3 = m1 * 2;
    m3.print();

    // element wise lambda.
    m1.modify([](auto& el) { return el * 2; });
    m1.print();

    // Access and write individual elements.
    std::cout << m1(1, 1) << std::endl;
    m1(1, 1) = 10;
    m1.print();

	return 0;
}