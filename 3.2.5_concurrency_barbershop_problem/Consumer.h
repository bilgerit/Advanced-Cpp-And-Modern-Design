// Consumer class for barbershop problem. Represents the barber.
// Holds a reference to the Barbershop it is visiting.
// Tobias Bilgeri, 12.7.2023
#pragma once
#include <string>
#include "Barbershop.h"

class Consumer {
    // Consumer == Barber in the barbershop problem (since the barber empties the queue).
    // Callable object.
    BarberShop& shop;
    const int serviceDuration;
    bool isSleeping{ true };

public:
    explicit Consumer(BarberShop& shop, const int& serviceDuration);

    void operator()();
};