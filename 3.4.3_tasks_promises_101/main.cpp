// In this exercise, we look at the basics of promise types.
// Promise types are a counterpart to futures (and can be used to create associated futures).
// One way to use them is to declare them in an empty state, and at a later point give them a value via
// p.set_value(). This value will then be passed on to the future once .get() is called.
// Tobias Bilgeri, 7. Dec. 2023
#pragma once
#include <future>
#include <iostream>
#include <thread>
#include <numbers>


int main() {
	std::promise<int> p1;  // default
	std::promise<int> p2 = std::promise<int>();  // empty shared state
	std::promise<int> p3 = std::move(p2);  // move
	
	std::promise<double> p4;
	auto f4 = p4.get_future();  // get associated future type object from a promise

	std::jthread t1(
		[/*Pass f4 by reference such that this thread will notice when it changes.*/ &f4]() {
			
			// Wait for value from promise. This will make the thread wait until
			// a value is set and the thread is joined.
			// If no value is set, we will wait forever.
			auto value = f4.get();
			std::cout << "Value from promise: " << value << std::endl;
		}
	);

	std::cout << "About to set value of the promise.\n";
	p4.set_value(std::numbers::pi);

	std::cout << "About to join the thread.\n";
	t1.join();
	return 0;
};