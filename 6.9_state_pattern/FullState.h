// FullState Class
// Tobias Bilgeri, 10.02.2024
#pragma once
#include "StackState.h"
#include "Stack.h"

class FullState : public StackState{
public:
    ~FullState() override = default;

    void Push(Stack& stack, int element) override;
    int Pop(Stack& stack) override;

    static FullState* instance();
};
