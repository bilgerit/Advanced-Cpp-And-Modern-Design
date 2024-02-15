#include <stdexcept>
#include "NotFullNotEmptyState.h"
#include "FullState.h"
#include <iostream>

void FullState::Push(Stack& stack, int element)
{
    throw std::runtime_error("Attempted to Push into a full stack.");
}

int FullState::Pop(Stack& stack)
{
    stack.currentIndex_ -= 1;
    stack.CheckTransition();
    return stack.elements_[stack.currentIndex_];
}

FullState* FullState::instance()
{
    return Singleton<FullState>::instance();
}