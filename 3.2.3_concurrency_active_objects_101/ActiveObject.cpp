#pragma once
#include "ActiveObject.h"

ActiveObject::ActiveObject(std::jthread& other) : t(other) {
	// Sole defined constructor. Explicitly accepts only a thread and stores it as member var.
	if (!this->t.joinable()) {
		throw std::runtime_error("ActiveObject: Attempted to construct ActiveObject with non-joinable thread. Possibly thread has no associated function or was joined already.");
	}
}

ActiveObject::~ActiveObject() {
	if (t.joinable()) {
		t.join();
	}
}