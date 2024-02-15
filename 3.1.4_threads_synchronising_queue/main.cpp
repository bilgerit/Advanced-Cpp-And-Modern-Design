// In this exercise, we ...
// Tobias Bilgeri, 3. Dec. 2023
#pragma once
#include "SynchronisingQueue.h"
#include "Producer.h"
#include "Consumer.h"
#include <thread>


int main() {

    // Thread-safe queue
    SynchronisingQueue<int> q{};

    // Producers which will move data into the queue: 
    Producer p1( &q, 1, { 1,2,3,4,5,6,7,8,9} );
    Producer p2( &q, 2, { 1,2,3,4,5,6} );
    Producer p3( &q, 3, { 1,2,3 } );

    // Consumers:
    Consumer c1(&q, 1);
    Consumer c2(&q, 2);

    // Creating the threads from funciton objects:

    // Note: this won't work -- cant just pass a callable object: std::jthread t1(p1);
    // These two methods of creating the threads will work:
    // std::thread t1(&Producer<int>::operator(), &p1);   // more complex: member fct reference + object reference
    std::jthread t1(std::ref(p1));                  // simple: std::reference_wrapper<Producer<int>>

    std::jthread t2(std::ref(p2));
    std::jthread t3(std::ref(p3));
    std::jthread t4(std::ref(c1));
    std::jthread t5(std::ref(c2));

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    std::cout << "\n\nResult -- data held by the consumers:\n";
    std::cout << c1.to_string();
    std::cout << c2.to_string() << std::endl;

    return 0;
}