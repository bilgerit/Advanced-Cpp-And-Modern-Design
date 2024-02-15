// State Pattern
//
// We implement a finite state machine using a custom stack.
// The custom stack can be in 3 distinct states:
//     - EmptyState
//     - FullState
//     - NotFullNotEmptyState
//
// Tobias Bilgeri, 10.02.2024
#pragma once
#include <iostream>
#include "Stack.h"

int main() {
    // create stack
    constexpr int size = 7;
    Stack stack(size);

    // fill the stack
    for (int i = 0; i < size; ++i) {
        std::cout << "Push: " << i << std::endl;
        stack.Push(i);
    }

    // empty the stack
    for (int i = 0; i < size; ++i) {
        std::cout << "Pop: " << stack.Pop() << std::endl;
    }

    return 0;
}