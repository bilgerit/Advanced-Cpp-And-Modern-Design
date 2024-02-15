// In this exercise, we ...
// Tobias Bilgeri, 05.01.2024
#pragma once
#include <iostream>
#include <numeric>
#include <complex>
#include "Vector.h"
#include "Matrix.h"


// a: inner prod
template <typename T> 
using BinaryFunction = std::function < T(const T& t1, const T& t2)>;

template <typename T, int N>
T inner_product(const Vector<T, N>& v1, const Vector<T, N>& v2, T initValue) {
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), initValue);
}

template <typename T, int N>
T inner_product(const Vector<T, N>& v1, const Vector<T, N>& v2, T initValue, const BinaryFunction<T>& op1, const BinaryFunction<T>& op2) {
    // pseudo-inner product w/ additional operations when computing the sum: sum = op1( sum, op2 ( a, b ) ) .. for (a,b) in (v1,v2)
    // reduces to regular inner product for op1==ADD, op2==MUL
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), initValue, op1, op2);
}

template<typename T>
const BinaryFunction<T> ADD = [](const T& a, const T& b) -> T { return a + b; };

template<typename T>
const BinaryFunction<T> MUL = [](const T& a, const T& b) -> T { return a * b; };


// d: outer prod
template <typename T, int N>
Matrix<T, N, N> outer_product(const Vector<T, N>& u, const Vector<T, N>& v) {
    Matrix<T, N, N> result;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result(i, j) = u[i] * v[j];
        }
    }
    return result;
}

// e: outer prod: complex numbers
template <int N>
Matrix<std::complex<double>, N, N> outer_product(const Vector<std::complex<double>, N>& u, const Vector<std::complex<double>, N>& v) {
    Matrix<std::complex<double>, N, N> result;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result(i, j) = u[i] * std::conj(v[j]);
        }
    }
    return result;
}


int main() {

    // b: inner product
    using f32_t = float;

    Vector<f32_t, 3> v1 { 1.0, 2.0, 3.0 };
    Vector<f32_t, 3> v2 { 1.0, 2.0, 3.0 };
    f32_t initValue = 0.0;
    std::cout << inner_product(v1, v2, initValue) << std::endl;

    // c: inner product w/ explicitly defined binary functions
    std::cout << inner_product(v1, v2, initValue, ADD<f32_t>, MUL<f32_t>) << std::endl;

    // d: outer product
    outer_product(v1, v2).print();

    // e: outer product w/ complex number
    Vector<std::complex<double>, 3> v3 { {1.0, 1.0}, {2.0, -2.0}, {3.0, 3.0} };
    Vector<std::complex<double>, 3> v4 { {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0} };

    outer_product(v3, v3).print();

	return 0;
}