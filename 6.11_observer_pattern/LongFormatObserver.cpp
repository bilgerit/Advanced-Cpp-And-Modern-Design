// Tobias Bilgeri, 11.02.2024
#include <iostream>

#include "LongFormatObserver.h"
#include "Subject.h"
#include "Counter.h"

void LongFormatObserver::Update(Subject* subject) {
    Counter* counter = static_cast<Counter*>(subject);
    long val = counter->Value();
    std::cout << "LongFormatObserver: " << val << "\n";
}
