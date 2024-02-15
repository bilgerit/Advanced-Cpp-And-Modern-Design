// Tobias Bilgeri, 11.02.2024
#include <iostream>
#include <iomanip>

#include "DoubleFormatObserver.h"
#include "Subject.h"
#include "Counter.h"

void DoubleFormatObserver::Update(Subject* subject) {
    Counter* counter = static_cast<Counter*>(subject);
    double val = counter->Value();
    std::cout << "DoubleFormatObserver: " << std::fixed << std::setprecision(2) << val << "\n";
}
