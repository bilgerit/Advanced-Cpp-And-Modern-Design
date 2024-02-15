// In this exercise, we demonstrate how multi-threaded usage of smart pointers leads to a race condition.
// Tobias Bilgeri, 3. Dec. 2023
#pragma once
#include <iostream>
#include <memory>
#include <atomic>
#include <chrono>
#include <random>
#include <thread>
#include <array>


struct X {
	double val{ 0.0 };
	X() = default;
	void operator ()() const { std::cout << "An X " << val << std::endl; }
};

template <typename T> using GenericPointerType = std::shared_ptr<T>; 
using PointerType = GenericPointerType<X>;

void Modify(const PointerType& p, double newVal) {

	// Wait a while, long enough to trigger the race 

	// Create a static random number generator. Make it static since there is no need to recreate this utility at each function call.
	static std::random_device rd;  // Will be used to obtain a seed for the random number engine
	static std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	static std::uniform_int_distribution distrib(1, 10'000); // Uniform integer distrib between 1 and 1e5
	
	// Sleep for a random number of microseconds.
	int timeToSleep = distrib(gen);
	std::this_thread::sleep_for(std::chrono::microseconds(timeToSleep));

	// Assign new value to p->val
	p->val = newVal; 
	
	// Print the result to console.
	p->operator()();
	// We will see that despite trying to assign and subsequently print 100 unique values, only a of these is actually displayed,
	// and many will be displayed multiple time, which is a result of the race condition. This could be easily solved by
	// for example using a lock.
}

int main() {

	// Create the shared pointer object.
	auto x = std::make_shared<X>();

	// Set up the threads.
	const int arraySize{ 100 };
	std::array<std::jthread, arraySize> threadArray;

	for (int i = 0; i != arraySize; i++) {
		threadArray[i] = std::jthread(
			Modify, 
			std::ref(x),  // creates a reference_wrapper object (copy-constructible and copy-assignable) (see: stackoverflow.com/questions/33240993/what-is-the-advantage-of-stdref-and-stdreference-wrapper-compared-to-regular) 
			i);
	}

	// Join the threads.
	for (auto& thread : threadArray) {
		thread.join();
	}

	return 0;
};