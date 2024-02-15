// Proposition class declarations.
// Proposition class contains a bitset with a single element and various overloaded operations defined.
// Tobias Bilgeri, 01.01.2024
#pragma once
#include <bitset>

class Proposition {
    // Contains a bitset with a single element and various overloaded operations defined.
private:
    std::bitset<1> _data;

public:
    Proposition();
    Proposition(bool b);
    Proposition(std::bitset<1> b);

    bool operator == (const Proposition& other) const;
    bool operator != (const Proposition& other) const;
    Proposition operator & (const Proposition& other) const;
    Proposition operator | (const Proposition& other) const;
    Proposition operator ^ (const Proposition& other) const;
    Proposition operator ! () const;
    Proposition& operator = (bool b);

    friend Proposition operator % (const Proposition& lhs, const Proposition& rhs);
    friend Proposition operator <=> (const Proposition& lhs, const Proposition& rhs);
};