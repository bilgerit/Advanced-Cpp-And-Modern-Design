// Producer class for barbershop problem.
// Tobias Bilgeri, 12.7.2023
#pragma once
#include "Barbershop.h"

class Producer {
    // Producer class for the barbershop problem.
    // When the object is called, it will call the enter_shop method of the barbershop,
    // wherein it will simply pass on it's <id> member var.
    int id;
    BarberShop& shop;

public:
    Producer(int id, BarberShop& shop);

    bool operator()();
};