// NotFullNotEmptyState Class
// Tobias Bilgeri, 10.02.2024
#pragma once
#include "FullState.h"
#include "StackState.h"
#include "Singleton.hpp"

class NotFullNotEmptyState : public StackState, public Singleton<StackState> {
public:
    ~NotFullNotEmptyState() override = default;

    void Push(Stack& stack, int element) override;
    int Pop(Stack& stack) override;

    static NotFullNotEmptyState* instance();
};