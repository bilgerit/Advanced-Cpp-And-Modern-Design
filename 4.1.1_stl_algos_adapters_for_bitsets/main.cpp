// In this exercise, we create a Proposition abstraction, which is a thin wrapper around
// std::bitset<1>, with various logical operations defined.
// Tobias Bilgeri, 01. 01. 2024
#pragma once
#include "Proposition.h"
#include <iostream>
#include <cassert>

int main() {
    // Test constructors
    Proposition p1;
    assert(p1 == Proposition(false));

    Proposition p2(true);
    assert(p2 == Proposition(true));

    Proposition p3(std::bitset<1>(1));
    assert(p3 == Proposition(true));

    // Test operators
    Proposition p4(true);
    Proposition p5(false);

    assert((p4 & p5) == Proposition(false));
    assert((p4 | p5) == Proposition(true));
    assert((p4 ^ p5) == Proposition(true));
    assert((!p4) == Proposition(false));
    assert((p4 % p5) == Proposition(false));
    assert((p4 <=> p5) == Proposition(false));

    // Test De Morgan's Laws
    assert(!(p4 | p5) == (!p4 & !p5));
    assert(!(p4 & p5) == (!p4 | !p5));

    // Test Distributive Laws
    Proposition p6(true);

    assert((p4 & (p5 | p6)) == ((p4 & p5) | (p4 & p6)));
    assert((p4 | (p5 & p6)) == ((p4 | p5) & (p4 | p6)));

    // Test Tautology
    for (bool a : {false, true}) {
        for (bool b : {false, true}) {
            for (bool c : {false, true}) {
                Proposition pA(a);
                Proposition pB(b);
                Proposition pC(c);
                assert((pA % (pB % pC)) <=> ((pA & pB) % pC) == Proposition(true));
            }
        }
    }

    std::cout << "All tests passed!" << std::endl;

    return 0;
}