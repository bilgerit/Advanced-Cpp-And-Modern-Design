#include <algorithm>
#include <iostream>

#include "Stack.h"
#include "EmptyState.h"
#include "FullState.h"
#include "NotFullNotEmptyState.h"


void Stack::Init(int size)
{
    size_ = std::max(1, size);
    currentIndex_ = 0;
    elements_ = new int[size_];
    state_ = new EmptyState();
}

Stack::Stack()
{
    this->Init(1);
}

Stack::Stack(int size)
{
    Init(size);
}

Stack::~Stack()
{
    delete elements_;
    delete state_;
}

void Stack::Push(int element)
{
    state_->Push(*this, element);
}

int Stack::Pop()
{
    return state_->Pop(*this);
}

const StackState* Stack::State() const
{
    return state_;
}

void Stack::CheckTransition()
{
    if (currentIndex_ == 0)
    {
        state_ = EmptyState::instance();
        std::cout << " (Transitioned to EmptyState) ";
        return;
    }

    if (currentIndex_ == size_)
    {
        state_ = FullState::instance();
        std::cout << " (Transitioned to FullState) ";
        return;
    }

    if (state_ != NotFullNotEmptyState::instance())
    {
        state_ = NotFullNotEmptyState::instance();
        std::cout << " (Transitioned to NotFullNotEmptyState) ";
    }
    return;
}
