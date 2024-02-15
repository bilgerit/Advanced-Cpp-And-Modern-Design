// Proposition class implementations.
// Tobias Bilgeri, 01.01.2024
#pragma once
#include "Proposition.h"

Proposition::Proposition() : _data(0) {}
Proposition::Proposition(bool b) : _data(b) {}
Proposition::Proposition(std::bitset<1> b) : _data(b) {}

bool Proposition::operator == (const Proposition& other) const {
    return _data == other._data;
}

bool Proposition::operator != (const Proposition& other) const {
    return _data != other._data;
}

Proposition Proposition::operator & (const Proposition& other) const {
    return Proposition(_data & other._data);
}

Proposition Proposition::operator | (const Proposition& other) const {
	// OR
    return Proposition(_data | other._data);
}

Proposition Proposition::operator ^ (const Proposition& other) const {
	// XOR
    return Proposition(_data ^ other._data);
}

Proposition Proposition::operator ! () const {
    auto negated = _data;
    return Proposition(negated.flip());
}

Proposition& Proposition::operator = (bool b) {
    _data = b;
    return *this;
}

Proposition operator % (const Proposition& lhs, const Proposition& rhs) {
	// Conditional operator
    if ((lhs._data == true) && (rhs._data == false)) return Proposition(false);
    return Proposition(true);
}

Proposition operator <=> (const Proposition& lhs, const Proposition& rhs) {
	// Biconditional operator
    return (lhs % rhs) & (rhs % lhs);
}