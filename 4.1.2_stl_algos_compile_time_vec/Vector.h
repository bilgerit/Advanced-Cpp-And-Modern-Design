// Vector class. 
// Implemented as a wrapper around a stack-allocated C-style array.
// Tobias Bilgeri, 03.01.2024
#pragma once
#include <initializer_list>
#include <algorithm>
#include <functional>

template <typename _Elem, size_t _N>
class Vector {
    // Compile-time vector. 
    // ('vector' as in maths and vector space, not as in 'flexible array'). 
    // Similar to std::array, but w/ vector-space arithmetics implemented. 
    // 
    // Warning: We do not perform any runtime bound checking. Make sure to not go out of bounds.
private:
    _Elem array[_N];

public:
    // Constructors
    Vector() = default;
    Vector(const Vector& other) = default;
    Vector(Vector&& other) noexcept = default;
    Vector& operator = (const Vector& other) = default;
    Vector& operator = (Vector&& other) noexcept = default;
    explicit Vector(const std::initializer_list<_Elem>& il) noexcept;

    // Element access, iterators
    const _Elem& operator [] (const size_t index) const;
    _Elem& operator [] (const size_t index);

    _Elem* begin();
    _Elem* end();
    const _Elem* begin() const;
    const _Elem* end() const;

    // Arithmetics
    Vector operator + (const Vector& other) const;
    Vector operator - (const Vector& other) const;
    Vector operator - () const;
    Vector operator * (const _Elem scalar) const;
    Vector hadamard(const Vector& other) const;
    _Elem dot(const Vector& other) const;

    template <typename Type, size_t N, typename F>
    friend Vector<Type, N> operator * (const F& a, const Vector<Type, N>& pt);

    void modify(const std::function<_Elem(const _Elem&)>& f);
};

#include "Vector.cpp"