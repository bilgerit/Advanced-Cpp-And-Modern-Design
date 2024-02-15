// Stack Class
// Tobias Bilgeri, 10.02.2024
#pragma once
#include <string>
class StackState;

class Stack {
private:
    int* elements_;
    int size_;
    int currentIndex_;
    StackState* state_;

    void Init(int size);

public:
    Stack();
    Stack(int size);
    ~Stack();
    void Push(int element);
    int Pop();
    const StackState* State() const;
    void CheckTransition();

    friend class EmptyState;
    friend class NotFullNotEmptyState;
    friend class FullState;
};
