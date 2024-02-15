// In this exercise, we look at the basics of async threads.
// Specifically, there are differing launch policies: default, async, deferred.
// Compared to regular threads, they neatly support returning values via std::future.
// Tobias Bilgeri, 3. Dec. 2023
#pragma once
#include <iostream>
#include <thread>
#include <future>


void func1() {
    std::cout << " - running func1 - \n";
}

double func2(double a, double b) {
    std::cout << " - running func2 - \n";
    return a + b;
}


int main() {
    // Use std::future as return type for async thread
    // std::future stops being valid after .get() is called.
    // .get() blocks the current thread until we can retrieve the result.
    // Note that without specifying the launch policy as std::launch::async or
    // std::launch::deferred, either one might end up happening (decided by the system).
    std::cout << "\n\nDefault Launch Policy\n\n";
    auto future1 = std::async(func1);
    std::cout << "Future1 valid: " << future1.valid() << "\n"; // True
    future1.get();
    std::cout << "Future1 valid: " << future1.valid() << "\n"; // False

    auto future2 = std::async(func2, 1.0, 2.0);
    std::cout << "Future2 valid: " << future2.valid() << "\n"; // True
    auto r2 = future2.get(); // double
    std::cout << "Future2 result: " << r2 << "\n"; // False
    std::cout << "Future2 valid: " << future2.valid() << "\n";

    // Question C
    // If we try go get the results of a std::future object more than once, 
    // it will return a std::future_error with error condition
    // std::future_errc::no_state.

    // Question D
    // with std::launch:async, the functions are guaranteed to execute in a seperate
    // thread, and the thread is started immediately.
    std::cout << "\n\nAsync Launch Policy\n\n";
    auto future3 = std::async(std::launch::async, func1);
    future3.get();

    auto future4 = std::async(std::launch::async, func2, 1.0, 2.0);
    auto r4 = future4.get();
    std::cout << "Future4 result: " << r4 << "\n";

    // Question E
    // with std::launch::deferred, the functions can be executed at a later point in time.
    std::cout << "\n\nDeferred Launch Policy\n\n";
    auto future5 = std::async(std::launch::deferred, func1);
    future5.get();

    auto future6 = std::async(std::launch::deferred, func2, 1.0, 2.0);
    auto r6 = future6.get();
    std::cout << "Future6 result: " << r6 << "\n";

	return 0;
};