// Thread-safe priority queue.
// Tobias Bilgeri, 14.12.2023
#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

template<class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
class SynchronisingPriorityQueue {
	// Thread-safe priority queue.
private:
	mutable std::mutex m;  // mutable keyword s.t. mutex is mutable even if Container is const.
	std::condition_variable cv;
	std::priority_queue<T, Container, Compare> pq;

public:
	void push(const T& t);
	T pop();
};

#include "SynchronisingPriorityQueue.cpp"