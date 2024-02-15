#pragma once
#include "Consumer.h"


template <typename T>
Consumer<T>::Consumer(SynchronisingQueue<T>* q, int id) : _q(q), _id(id) {
	_msg = std::format("Consumer {} just consumed.\n", id);
}

template <typename T>
void Consumer<T>::operator() () {
	// Dequeue from synchronizing queue pointer. If value is found, add it to consumed values, and print information to console.
	while (true) {
		std::optional<T> retval = _q->dequeue();
		if (retval.has_value()) {
			std::cout << std::format("(Value={}) ", retval.value()) + _msg;
			_consumed.push_back(retval.value());
		}
		else {
			return;
		}
	}
}

template <typename T>
std::string Consumer<T>::to_string() const{
	std::stringstream ss;
	ss << "Consumer " << _id << " consumed: ";
	for (auto& el : _consumed) {
		ss << el;
	}
	ss << ".\n";
	return ss.str();
}
