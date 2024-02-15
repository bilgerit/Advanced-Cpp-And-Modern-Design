// Counter class: Subject Impl
//
// Wrapper around an integer which can be increased and decreased.
// Is derived from Subject and hence can be used with our Observer pattern.
//
// Tobias Bilgeri, 11.02.2024
#pragma once
#include "Subject.h"

class Counter : public Subject {
private:
    int value_ = 0;
public:
    int Value() const;
    void IncreaseCounter();
    void DecreaseCounter();
};
