// Barbershop problem:
// Single consumer (barber) empties the queue populated by producers.
// Barbershop itself is a wrapper around the synchronizing queue and handles interactions
// of the producer and consumer with the queue.
// Tobias Bilgeri, 3. Dec. 2023
#pragma once
#include "Producer.h"
#include "Consumer.h"

int main() {
    // ----------------------------------------------------
    // Variables (all time units are in s)
    int serviceDurationPerCustomer{ 2 };
    int interArrivalPeriod{ 10 };  // Exercise asks for 10
    int maxChairs{ 5 };
    int numCustomers{ 8 };
    // ----------------------------------------------------


    BarberShop shop(maxChairs);
    Consumer barber{ shop, serviceDurationPerCustomer };

    // Start barberthread. Ends in a while(true) construct.
    std::jthread barberThread(std::ref(barber));

    for (int customer_id = 0; customer_id != numCustomers; customer_id++) {
        // Create new Barbershop customer.
        Producer producer(customer_id, shop);

        // Processes the event (customer arrival) in a seperate thread.
        // Producer will call shop's enter_shop method and it's ID will get added to
        // the queue if not all chairs are occupied yet, or rejected.
        // And since the thread is so simple, we can just detach it (alternatively:
        // store them in array and individually join them later).
        std::jthread(std::ref(producer)).detach();

        // wait a certain time until we let next customer arrive.
        std::this_thread::sleep_for(std::chrono::seconds(interArrivalPeriod)); 
    }

    shop.close_shop();
    if (barberThread.joinable()) barberThread.join();

    return 0;
}