#pragma once
#include "Consumer.h"

Consumer::Consumer(BarberShop& shop, const int& serviceDuration) : shop(shop), serviceDuration(serviceDuration) {}

void Consumer::operator()() {
    // Make Barber callable so that we can pass it to a thread.
    while (true) {

        std::optional<int> id = shop.next_customer();

        // No customer in queue?
        if (!id.has_value()) {

            // Shop closed?
            if (!shop.isOpen()) {
                std::cout << "Barber goes home.";
                return;
            }

            // Already sleeping?
            if (isSleeping) continue;

            // Start sleeping!
            std::cout << "Barber starts sleeping.\n";
            isSleeping = true;
            continue;
        }

        // Already sleeping? Wake up!
        if (isSleeping) {
            std::cout << "Barber woke up.\n";
            isSleeping = false;
        }

        // Start working on a customer.
        std::cout << ("Barber starts serving customer " + std::to_string(id.value()) + ".\n");
        std::this_thread::sleep_for(std::chrono::seconds(serviceDuration)); // simulate time it takes to serve a customer
        std::cout << ("Barber finishes serving customer " + std::to_string(id.value()) + ".\n");
    }
}