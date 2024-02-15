// Tobias Bilgeri, 11.02.2024
#include "Counter.h"

int Counter::Value() const {
    return value_;
}
void Counter::IncreaseCounter() {
    // increase the counter and notify observers
    ++value_;
    Notify();
}
void Counter::DecreaseCounter() {
    // decrease the counter and notify observers
    --value_;
    Notify();
}
