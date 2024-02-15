// In this exercise, we create a synchronising priority queue.
// Tobias Bilgeri, 14. Dec. 2023
#pragma once
#include <iostream>
#include <array>
#include <random>
#include <chrono>
#include "SynchronisingPriorityQueue.h"

int main() {
	// Test the class:
	// Create a set of producer and consumer threads with stochastic arrival rate.
	// Producers add to the queue, consumers remove and print.
	// Note that I use jthread objects, hence no need to manually join.
	SynchronisingPriorityQueue<int> spq;

	const int numThreads = 40;
	std::vector<std::jthread> threads;

	std::mt19937 mt(42);
	std::uniform_int_distribution randInt(1, 5000);
	int randDelay;

	for (int i = 0; i != numThreads; i++) {

		randDelay = randInt(mt);

		// Create Producer
		if (i % 2 == 0) {
			threads.emplace_back([&spq, i, randDelay]() -> void { 
				std::this_thread::sleep_for(std::chrono::milliseconds(randDelay));
				spq.push(i/2); 
				}
			);
		} 
		// Create Consumer
		else {
			threads.emplace_back([&spq, i, randDelay]() -> void {
				std::this_thread::sleep_for(std::chrono::microseconds(randDelay));
				std::cout << (std::to_string(spq.pop()) + "\n");
				}
			);
		}
	}

	return 0;
};