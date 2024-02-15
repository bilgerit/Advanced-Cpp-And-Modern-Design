// Compile-time matrix.
// Implemented as an array of arrays using std::array.
// Contains various methods for arithmetics.
// Tobias Bilgeri, 03.01.2024
#pragma once
#include <array>
#include <initializer_list>
#include <functional>
#include <algorithm>
#include <iostream>

template <typename _Elem, size_t NR, size_t NC>
class Matrix {
    // Compile-time matrix class.
    // Implemented as std::array containing std::array<T> types.
    // Contains various methods for arithmetics.
private:
    std::array<std::array<_Elem, NC>, NR> mat;

public:
    // Constructors
    Matrix() = default;
    explicit Matrix(_Elem value);  // uniform value initialization;
    Matrix(const Matrix& other) = default;
    Matrix& operator = (const Matrix& other) = default;
    explicit Matrix(const std::initializer_list<std::initializer_list<_Elem>>& il);

    // Element access
    const _Elem& operator () (size_t row, size_t col) const;
    _Elem& operator () (size_t row, size_t col);

    void print() const;

    // Arithmetics
    Matrix operator + (const Matrix& other) const;
    Matrix operator - (const Matrix& other) const;
    Matrix operator - () const;
    Matrix operator * (const _Elem scalar) const;

    template <typename Type, size_t _NR, size_t _NC, typename F>
    Matrix<Type, _NR, _NC> friend operator * (const F& a, const Matrix<Type, _NR, _NC >& mat);

    void modify(const std::function <_Elem(_Elem&)>& f);
};

#include "Matrix.cpp"