// Consumer class.
// Tobias Bilgeri, 6 Dec 2023.
#pragma once
#include "SynchronisingQueue.h"
#include <vector>
#include <initializer_list>
#include <iostream>
#include <string>
#include <sstream>
#include <format>


template<typename T>
class Consumer {
	// Simple consumer class. 
	// Has the relevant queue and an ID assigned when constructed.
	// Then tries to fetch everything from the queue element-by-element when called with operator () until the queue is empty.
private:
	SynchronisingQueue<T>* _q;
	int _id;
	std::string _msg;
	std::vector<T> _consumed;

public:
	Consumer(SynchronisingQueue<T>* q, int id);
	~Consumer() = default;

	Consumer() = delete;
	Consumer(const Consumer& p) = delete;
	Consumer(Consumer&& p) noexcept = delete;
	Consumer& operator = (const Consumer& p) = delete;
	Consumer& operator = (Consumer&& p) noexcept = delete;

	void operator () ();
	std::string to_string() const;
};

#include "Consumer.cpp"