// Producer class.
// Tobias Bilgeri, 6 Dec 2023.
#pragma once
#include "SynchronisingQueue.h"
#include <vector>
#include <initializer_list>
#include <iostream>
#include <string>
#include <format>
#include <thread>


template<typename T>
class Producer {
	// Simple producer class. 
	// Has a set of values to produce as well as the relevant queue and an ID assigned when constructed.
	// Then sends all values to the queue when called with operator ().
private:
	SynchronisingQueue<T>* _q;
	int _id;
	std::vector<T> _to_produce;
	std::string _msg;

public:
	Producer(SynchronisingQueue<T>* q, const int id, const std::initializer_list<T> list);
	~Producer() = default;

	Producer() = delete;
	Producer(const Producer& p) = delete;
	Producer(Producer&& p) noexcept = delete;
	Producer& operator = (const Producer& p) = delete;
	Producer& operator = (Producer&& p) noexcept = delete;

	void operator () ();
};

#include "Producer.cpp"