#include <stdexcept>
#include "NotFullNotEmptyState.h"
#include "EmptyState.h"
#include <iostream>

void EmptyState::Push(Stack& stack, int element)
{
    stack.elements_[0] = element;
    stack.currentIndex_ = 1;
    stack.CheckTransition();
}

int EmptyState::Pop(Stack& stack)
{
    throw std::runtime_error("Attempted to Pop from empty stack.");
}

EmptyState* EmptyState::instance()
{
    return Singleton<EmptyState>::instance();
}
