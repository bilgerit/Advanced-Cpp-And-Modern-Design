// Tobias Bilgeri, 11.02.2024
#include "Subject.h"
#include "Observer.h"

void Subject::Attach(Observer* observer) {
    // add new observer to vector of observers.
    observers_.push_back(observer);
}

void Subject::Detach(Observer* observer) {
    // find an observer in the vector of observers and remove it.
    std::erase(observers_, observer);
}

void Subject::Notify() {
    // update all attached observers
    for (Observer* observer : observers_) {
        observer->Update(this);
    }
}
