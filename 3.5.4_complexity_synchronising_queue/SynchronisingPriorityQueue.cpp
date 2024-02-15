#pragma once
#include "SynchronisingPriorityQueue.h"

template<typename T, typename Container, typename Compare>
void SynchronisingPriorityQueue<T, Container, Compare>::push(const T& t) {
	std::lock_guard<std::mutex> lock(m);
	pq.push(t);
	// If other threads are sleeping & waiting for the queue to be repopulated:
	// wake at least one of them up.
	cv.notify_one();
}

template<typename T, typename Container, typename Compare>
T SynchronisingPriorityQueue<T, Container, Compare>::pop() {
	std::unique_lock<std::mutex> lock(m);
	// If pq is empty: temporarely release lock.
	// This allows other threads to continue working with pq.
	// This thread will sleep until it is woken up by a cv.nofity_one() call.
	// If !pq.empty() still evaluates to false, it will go back to sleep again.
	// Note that the 2nd arg of cv.wait should here be a callable, and we use a 
	// lambda to get a clean single-line implementation, and capture the this pointer
	// by value, which allows the lambda to access member functions.
	cv.wait(lock, [this] { return !pq.empty(); });
	T val = pq.top();
	pq.pop();
	return val;
}
