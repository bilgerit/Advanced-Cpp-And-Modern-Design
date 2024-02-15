#pragma once
#include "Producer.h"


template <typename T>
Producer<T>::Producer(SynchronisingQueue<T>* q, const int id, const std::initializer_list<T> list) : _q(q), _id(id), _to_produce(list) {
	_msg = std::format("Producer {} just produced.\n", id);
}

template <typename T>
void Producer<T>::operator() () {
	// loop through _to_produce container and append it to thread safe queue stored via pointer, then print some information to console.
	for (auto& el : _to_produce) {
		_q->enqueue(el);
		std::cout << std::format("(Value={}) ", el) + _msg;
	}
}