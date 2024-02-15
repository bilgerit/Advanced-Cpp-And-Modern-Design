#pragma once
#include "SynchronisingQueue.h"


template<typename T>
void SynchronisingQueue<T>::enqueue(const T& el) {
	// Add element to back of the queue.

	// Zero cost RAII pattern. If mutex is already locked, this thread will
	// wait until the mutex becomes available to the lock.
	std::unique_lock ulock{ _mutex };

	// Add element to queue
	_q.push(el);

	// Notify possible other threads waiting for a condition variable signal
	// that the data is now available.
	_cv.notify_all();
}


template<typename T>
std::optional<T> SynchronisingQueue<T>::dequeue() {
	// Remove element at the front of the queue.
	// Will wait until new element is available if current queue size is zero.

	// Aquire lock (if necessary, wait until mutex is available).
	std::unique_lock ulock{ _mutex };

	// If queue is empty: wait until a producer populates it.
	if (_q.size() == 0) {
		// Wait (potentially indefinitely)
		// _cv.wait(ulock);

		// Alternatively: limit the time we spend potentially waiting.
		_cv.wait_for(ulock, consumer_wait_for_if_empty);
	}

	// If queue is still empty after waiting, return std::nullopt
	if (_q.empty()) {
		return std::nullopt;
	}

	// Get value at the front of the queue
	T retval = _q.front();

	// Remove value at the front of the queue
	_q.pop();

	// Return the value. Lock get's released automatically via the unique_lock
	// going out of scope.
	return retval;
}
