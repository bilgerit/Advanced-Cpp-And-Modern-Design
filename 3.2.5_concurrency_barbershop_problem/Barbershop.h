// BarberShop class. Implements the barbershop logic.
// Is composed of the synchronizing queue.
// Tobias Bilgeri, 7 Dec 2023.
#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include "SynchronisingQueue.h"

class BarberShop {
    // Barbershop class for the barbershop problem.
    // Can be open or close
    // Can hold a queue of customers with some max capacity.
    SynchronisingQueue<int> customers;
    const int max_chairs;
    bool is_open{ true };

public:
    explicit BarberShop(int n);
    bool isOpen() const;
    void close_shop();
    bool try_enter_shop(int id);
    std::optional<int> next_customer();
};
