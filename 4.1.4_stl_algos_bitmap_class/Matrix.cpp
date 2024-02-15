// Implementations for Matrix.h
// Tobias Bilgeri, 03.01.2024
#pragma once
#include "Matrix.h"

template <typename _Elem, size_t NR, size_t NC>
Matrix<_Elem, NR, NC>::Matrix(const std::initializer_list<std::initializer_list<_Elem>>& il) {
    size_t i = 0;
    for (const auto& row : il) {
        std::copy_n(row.begin(), std::min(row.size(), NC), mat[i].begin());
        ++i;
        if (i == NR) break;
    }
}

template <typename _Elem, size_t NR, size_t NC>
Matrix<_Elem, NR, NC>::Matrix(_Elem value) {
    // uniform value assignment
    for (auto& row : mat) {
        row.fill(value);
    }
}

template <typename _Elem, size_t NR, size_t NC>
const _Elem& Matrix<_Elem, NR, NC>::operator () (size_t row, size_t col) const {
    // element query (const)
    return mat[row][col];
}

template <typename _Elem, size_t NR, size_t NC>
_Elem& Matrix<_Elem, NR, NC>::operator () (size_t row, size_t col) {
    // element query (non-const)
    return mat[row][col];
}

template <typename V, size_t NR, size_t NC>
void Matrix<V, NR, NC>::print() const {
    // print elements
    for (const auto& row : mat) {
        for (const auto& elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
}

template <typename _Elem, size_t NR, size_t NC>
Matrix<_Elem, NR, NC> Matrix<_Elem, NR, NC>::operator + (const Matrix& other) const {
    // element-wise addition
    Matrix result;
    for (size_t i = 0; i < NR; ++i) {
        for (size_t j = 0; j < NC; ++j) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return result;
}

template <typename _Elem, size_t NR, size_t NC>
Matrix<_Elem, NR, NC> Matrix<_Elem, NR, NC>::operator - (const Matrix& other) const {
    // element-wise subtraction
    Matrix result;
    for (size_t i = 0; i < NR; ++i) {
        for (size_t j = 0; j < NC; ++j) {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return result;
}

template <typename _Elem, size_t NR, size_t NC>
Matrix<_Elem, NR, NC> Matrix<_Elem, NR, NC>::operator - () const {
    Matrix result;
    // element-wise unary minus
    for (size_t i = 0; i < NR; ++i) {
        for (size_t j = 0; j < NC; ++j) {
            result(i, j) = -(*this)(i, j);
        }
    }
    return result;
}

template <typename _Elem, size_t NR, size_t NC>
Matrix<_Elem, NR, NC> Matrix<_Elem, NR, NC>::operator * (const _Elem scalar) const {
    // element-wise multiplication
    Matrix result;
    for (size_t i = 0; i < NR; ++i) {
        for (size_t j = 0; j < NC; ++j) {
            result(i, j) = (*this)(i, j) * scalar;
        }
    }
    return result;
}

template <typename Type, size_t _NR, size_t _NC, typename F>
Matrix<Type, _NR, _NC> operator * (const F& a, const Matrix<Type, _NR, _NC>& mat) {
    Matrix<Type, _NR, _NC> result;
    for (size_t i = 0; i < _NR; ++i) {
        for (size_t j = 0; j < _NC; ++j) {
            result(i, j) = mat(i, j) * a;
        }
    }
    return result;
}

template <typename _Elem, size_t NR, size_t NC>
void Matrix<_Elem, NR, NC>::modify(const std::function<_Elem(_Elem&)>& f) {
    for (auto& row : mat) {
        std::transform(row.begin(), row.end(), row.begin(), f);
    }
}