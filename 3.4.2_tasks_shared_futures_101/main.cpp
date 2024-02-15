// In this exercise, we look at the basic properties of shared_future.
// Tobias Bilgeri, 7. Dec. 2023
#pragma once
#include <future>
#include <iostream>

int main() {

	// Exercise 1: Various ways to initialize and share data.

	// Default instance
	std::shared_future<int> sf1;

	// Shared future that shares the same state as another shared state
	sf1 = std::async(std::launch::async, []() { return 1; });
	std::shared_future<int> sf2{ sf1 };

	// Transfer shared state from a 'normal' future to a shared future
	std::future<int> f1 = std::async(std::launch::async, []() { return 1; });
	std::future<int> f2 = std::async(std::launch::async, []() { return 2; });
	std::shared_future sf3(std::move(f2));  
	std::shared_future sf33(f1.share()); 


	// Transfer shared state from a shared future to a shared future
	std::shared_future sf4(std::move(sf3));  // move state from shared_future to shared_future


	// Question B
	// Most member functions of future are also available for shared_future types,
	// such as valid(), wait(), wait_for(), wait_until(), get(), etc.
	// However, shared_future's get() method can be called multiple times,
	// multipe shared_futures can refer to the same state, and future is only movable,
	// not copyable.


	// Question C
	// Calling get twice on a shared_future returns the same result each time.
	std::cout << "sf2.get(): " << sf2.get() << std::endl;
	std::cout << "sf2.get(): " << sf2.get() << std::endl;

	
	// Question D
	// Enter infinite loop and time out
	std::shared_future<void> sf5 = std::async(
		std::launch::async, 
		[]() { while (true) { /* infinte loop */ }; }
	);

	if (sf5.wait_for(std::chrono::seconds(1)) == std::future_status::timeout) {
		std::cout << "sf5 timed out\n";
	}

	if (sf5.wait_until(std::chrono::steady_clock::now() + std::chrono::seconds(1)) == std::future_status::timeout) {
		std::cout << "sf5 timed out\n";
	}

	return 0;
};