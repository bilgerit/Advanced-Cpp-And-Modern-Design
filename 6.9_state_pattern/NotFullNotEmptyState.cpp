#include "NotFullNotEmptyState.h"
#include "FullState.h"
#include "EmptyState.h"
#include <iostream>

void NotFullNotEmptyState::Push(Stack& stack, int element)
{
    stack.elements_[stack.currentIndex_] = element;
    stack.currentIndex_ += 1;
    stack.CheckTransition();
}

int NotFullNotEmptyState::Pop(Stack& stack)
{
    stack.currentIndex_ -= 1;
    stack.CheckTransition();
    return stack.elements_[stack.currentIndex_];
}

NotFullNotEmptyState* NotFullNotEmptyState::instance()
{
    return Singleton<NotFullNotEmptyState>::instance();
}