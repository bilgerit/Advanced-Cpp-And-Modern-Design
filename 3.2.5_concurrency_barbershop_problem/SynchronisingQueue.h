// SynchronisingQueue class from exercise 3.1.4.
// Tobias Bilgeri, 6 Dec 2023.
#pragma once
#include <queue>
#include <mutex>
#include <optional>
#include <condition_variable>


template<typename T>
class SynchronisingQueue {
private:
	std::queue<T> _q;
	std::mutex _mutex;
	std::condition_variable _cv;

	// Consumers wait a fixed amount when queue is empty. If waiting longer than this,
	// they abandon.
	static constexpr auto consumer_wait_for_if_empty = std::chrono::milliseconds(10);

public:
	SynchronisingQueue() = default;
	~SynchronisingQueue() = default;

	// Dont allow any copy & move construction and assignment operations
	// (we could implement this but would also have to be made thread safe)
	SynchronisingQueue(const SynchronisingQueue<T>& other) = delete;
	SynchronisingQueue(SynchronisingQueue<T>&& other) = delete;
	SynchronisingQueue& operator = (const SynchronisingQueue<T>& other) = delete;
	SynchronisingQueue& operator = (SynchronisingQueue<T>&& other) = delete;

	// Queue utility: Add to back (enqueue), remove from front (dequeue).
	void enqueue(const T& el);
	std::optional<T> dequeue();
	size_t size() const { return _q.size(); };
};

#include "SynchronisingQueue.cpp"