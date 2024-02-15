// Observer Interface
//
// Derived classes must implement an Update method which
// updates some subject accessed via a pointer.
//
// Tobias Bilgeri, 11.02.2024
#pragma once
class Subject;

class Observer {
public:
    virtual ~Observer() {}
    virtual void Update(Subject* subject) = 0;
};
