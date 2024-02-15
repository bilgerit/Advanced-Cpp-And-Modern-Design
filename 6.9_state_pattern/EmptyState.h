// EmptyState Class
// Tobias Bilgeri, 10.02.2024
#pragma once
#include "StackState.h"
#include "Singleton.hpp"
#include "Stack.h"

class EmptyState : public StackState, public Singleton<StackState> {
public:
    ~EmptyState() override = default;

    void Push(Stack& stack, int element) override;
	int Pop(Stack& stack) override;

    static EmptyState* instance();
};
