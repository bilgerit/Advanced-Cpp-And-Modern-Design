// Subject Class
//
// Subject object connects to a variable number of observers
// stored in a vector.
// Observers can be attached, detached, and notified via
// specific methods.
//
// Tobias Bilgeri, 11.02.2024
#pragma once
#include <vector>

class Observer;

class Subject {
private:
    std::vector<Observer*> observers_;
public:
    void Attach(Observer* observer);
    void Detach(Observer* observer);
    void Notify();
};