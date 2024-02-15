// Implementation of Vector.
// Tobias Bilgeri, 03.01.2024
#pragma once
#include "Vector.h"

template <typename _Elem, size_t _N>
Vector<_Elem, _N>::Vector(const std::initializer_list<_Elem>& il) noexcept {
    std::copy_n(il.begin(), std::min(il.size(), _N), array);
}

template <typename _Elem, size_t _N>
const _Elem& Vector<_Elem, _N>::operator [] (const size_t index) const {
    return array[index];
}

template <typename _Elem, size_t _N>
_Elem& Vector<_Elem, _N>::operator [] (const size_t index) {
    return array[index];
}

template <typename _Elem, size_t _N>
_Elem* Vector<_Elem, _N>::begin() {
    return array;
}

template <typename _Elem, size_t _N>
_Elem* Vector<_Elem, _N>::end() {
    return array + _N;
}

template <typename _Elem, size_t _N>
const _Elem* Vector<_Elem, _N>::begin() const {
    return array;
}

template <typename _Elem, size_t _N>
const _Elem* Vector<_Elem, _N>::end() const {
    return array + _N;
}

template <typename _Elem, size_t _N>
Vector<_Elem, _N> Vector<_Elem, _N>::operator + (const Vector& other) const {
    Vector ans;
    for (size_t it = 0; it != _N; it++) {
        ans[it] = array[it] + other[it];
    }
    return ans;
}

template <typename _Elem, size_t _N>
Vector<_Elem, _N> Vector<_Elem, _N>::operator - (const Vector& other) const {
    Vector ans;
    for (size_t it = 0; it != _N; it++) {
        ans[it] = array[it] - other[it];
    }
    return ans;
}

template <typename _Elem, size_t _N>
Vector<_Elem, _N> Vector<_Elem, _N>::operator - () const {
    Vector ans;
    for (size_t i = 0; i < _N; ++i) {
        ans[i] = -array[i];
    }
    return ans;
}

template <typename _Elem, size_t _N>
Vector<_Elem, _N> Vector<_Elem, _N>::operator * (const _Elem scalar) const {
    Vector ans;
    for (size_t it = 0; it != _N; it++) {
        ans[it] = array[it] * scalar;
    }
    return ans;
}

template <typename _Elem, size_t _N>
Vector<_Elem, _N> Vector<_Elem, _N>::hadamard(const Vector& other) const {
    Vector ans;
    for (size_t it = 0; it != _N; it++) {
        ans[it] = array[it] * other[it];
    }
    return ans;
}

template <typename _Elem, size_t _N>
_Elem Vector<_Elem, _N>::dot(const Vector& other) const {
    _Elem ans = 0;
    for (size_t it = 0; it != _N; it++) {
        ans += array[it] * other[it];
    }
    return ans;
}

template <typename Type, size_t N, typename F>
Vector<Type, N> operator * (const F& a, const Vector<Type, N>& pt) {
    Vector<Type, N> ans;
    for (size_t it = 0; it != N; it++) {
        ans[it] = pt.array[it] * a;
    }
    return ans;
}

template <typename _Elem, size_t _N>
void Vector<_Elem, _N>::modify(const std::function<_Elem(const _Elem&)>& f) {
    for (size_t it = 0; it != _N; it++) {
        array[it] = f(array[it]);
    }
}