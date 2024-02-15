// StackState ABC
// Tobias Bilgeri, 10.02.2024
#pragma once
#include "Stack.h"

class StackState {
protected:
    StackState() {}
public:
    virtual ~StackState() = default;
    virtual void Push(Stack& stack, int element) = 0;
    virtual int Pop(Stack& stack) = 0;
};