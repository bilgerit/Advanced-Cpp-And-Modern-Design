#pragma once
#include "Barbershop.h"

BarberShop::BarberShop(int n) : max_chairs(n) {}

bool BarberShop::isOpen() const {
    return is_open;
}

void BarberShop::close_shop() {
    std::cout << "Shop is now closed. No new customers will be accepted. \n";
    is_open = false;
}

bool BarberShop::try_enter_shop(int id) {
    // Add customer to queue if there is still space (returns true). Else, return false.
    if (customers.size() < max_chairs) {
        std::cout << ("Customer " + std::to_string(id) + " enters the shop.\n");
        customers.enqueue(id);
        return true;
    }
    else {
        std::cout << ("Customer " + std::to_string(id) + " leaves because the shop is full.\n");
        return false;
    }
}

std::optional<int> BarberShop::next_customer() {
    // Serve next customer if shop is open and there are customers to serve.
    if (!is_open && customers.size() == 0) {
        return std::nullopt; // shop is closed and no customers are left
    }
    return customers.dequeue();
}