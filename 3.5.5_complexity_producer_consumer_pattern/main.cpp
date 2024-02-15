// In this exercise, we simulate a producers-consumer pattern using both boost and std.
// Notably, boost has several features that std in C++20 seems to lack, such as native
// 'thread_group' types and thread-safe lock-free queues.
// Tobias Bilgeri, 15. Dec. 2023
#pragma once

// Include comparable Boost & std libraries.
#include <boost/thread/thread.hpp>
#include <thread>

#include <boost/lockfree/queue.hpp>
#include <queue>

#include <boost/atomic.hpp>
#include <atomic>

#include <mutex>
#include <condition_variable>
#include <iostream>
#include <string>
#include <sstream>


// ====================================
// ====================================
// A) BOOST

// Shared thread-safe variables.
boost::atomic<bool> producersDoneBoost(false);    // atomic flag.
boost::atomic<int> consumerIDBoost(0);            // atomic counter.
boost::lockfree::queue<int> queueBoost(128);      // lock free queue.


void producerBoost() {
	// Simulate a group of producers.
	for (int i = 0; i != 4; i++) {
		queueBoost.push(i);
	}
}

void consumerBoost() {
	// Create consumer id from global atomic counter.
	int id = consumerIDBoost.fetch_add(1);

	int value;
	// While not all producers are done:
	while (!producersDoneBoost) {
		// While values are in queue:
		while (queueBoost.pop(value)) {
			std::stringstream ss;
			ss << "Boost consumer " << std::to_string(id) << " retrieved value: " << std::to_string(value) << "\n";
			std::cout << ss.str();
		}
	}
}

void mainBoost() {
	// Use thread group available in boost rather than std::array<std::thread> or similar.
	boost::thread_group producers;
	boost::thread_group consumers;
	for (int i = 0; i != 5; i++) {
		producers.create_thread(producerBoost);
	}
	for (int i = 0; i != 3; i++) {
		consumers.create_thread(consumerBoost);
	}
	producers.join_all();

	// Producers are done now.
	producersDoneBoost.store(true);

	consumers.join_all();
}


// ====================================
// ====================================
// B) Modern STD
std::atomic<bool> producersDoneStd(false);
std::atomic<int> counterStd(0);
std::queue<int> queueStd;
std::mutex mtx;
std::condition_variable cv;

void producerStd() {
	// Simulate a group of producers.
	// (to emulate multiple producers, each loop iteration has to aquire the lock separately.)
	for (int i = 0; i != 4; i++) {
		std::lock_guard lock(mtx);
		queueStd.push(i);

		// Since each producers produces only 1 queue element, it is enough to notify one.
		cv.notify_one();
	}
}

void consumerStd() {
	int id = counterStd.fetch_add(1);

	while (!producersDoneStd) {
		std::unique_lock lock(mtx);
		// Now: Wait if the producers are not finished and the queue is empty.
		cv.wait(lock, [] {return !queueStd.empty() || producersDoneStd; });
		while (!queueStd.empty()) {
			int value = queueStd.front();
			queueStd.pop();
			std::stringstream ss;
			ss << "STD consumer " << std::to_string(id) << " retrieved value: " << std::to_string(value) << "\n";
			std::cout << ss.str();
		}
	}
}

int mainStd() {
	std::jthread producers[5];
	std::jthread consumers[3];

	for (auto& p : producers) {
		p = std::jthread(producerStd);
	}

	for (auto& c : consumers) {
		c = std::jthread(consumerStd);
	}

	for (auto& p : producers) {
		p.join();
	}

	producersDoneStd.store(true);
	cv.notify_all();

	for (auto& c : consumers) {
		c.join();
	}
	return 0;
}

int main() {
	mainBoost();
	mainStd();
	return 0;
};