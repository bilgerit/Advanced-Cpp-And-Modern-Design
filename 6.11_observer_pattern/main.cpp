// Observer Pattern
//
// This pattern is composed of a Subject which may
// change it's state. Upon a change in state, we notify all
// Observers. The set of Observers can be expanded and shrank
// at runtime, making this a type of runtime-policy pattern.
//
// In this specific example, we simply have observers that print
// the (updated) state of an integer counter they are monitoring.
//
// Tobias Bilgeri, 11.02.2024
#pragma once
#include "Counter.h"
#include "LongFormatObserver.h"
#include "DoubleFormatObserver.h"


int main() {
    // Subject: counter
    Counter counter;

    // Observers:  
    LongFormatObserver longFormatObserver;
    DoubleFormatObserver doubleFormatObserver;

    // Attach observers to Subject
    counter.Attach(&longFormatObserver); // pass ref to stack allocated obj
    counter.Attach(&doubleFormatObserver);

    // Trigger Counter methods which change the subject and
    // notify the observers.
    counter.IncreaseCounter();
    counter.IncreaseCounter();
    counter.IncreaseCounter();
    counter.IncreaseCounter();

    // Detach longFormatObserver & Trigger again
    counter.Detach(&longFormatObserver);
    counter.DecreaseCounter();
    counter.DecreaseCounter();
    counter.DecreaseCounter();
    counter.DecreaseCounter();

    // Detach doubleFormatObserver
    counter.Detach(&doubleFormatObserver);

    return 0;
}