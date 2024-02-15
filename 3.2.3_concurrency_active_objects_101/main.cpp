// In this exercise, we take a look at Active Objects.
// Active Objects directly contain a reference to the thread they are running in.
// Similar to RAII patterns, in their destructor they also make sure that the thread
// is joined (if it wasn't joined earlier already).
// Tobias Bilgeri, 6. Dec. 2023
#pragma once
#include "ActiveObject.h"
#include <iostream>
#include <thread>

void simpleFunction() {
	// Simple free function to be called from a thread.
	std::cout << "Simple Free Function called.\n";
}

struct simpleFunctor {
	// Simple callable object to be called from a thread.
	void operator () () const {
		std::cout << "Simple Functor called.\n";
	}
};

void testActiveObject(std::jthread& t) {
	// Instantiate active object from thread.
	// Active object will join thread in destructor.
	// Active object will throw logic error if thread is not joinable.
	try {
		ActiveObject ao{ t };
	}
	catch (std::runtime_error& e) {
		std::cout
			<< "testing ActiveObject: Error caught when trying to create active object: "
			<< e.what()
			<< std::endl;
	}
}

int main() {
	// Use Free Function, Functor, and Lambda to create threads.
	std::jthread t1(simpleFunction);
	simpleFunctor callableObject;
	std::jthread t2(callableObject);
	std::jthread t3([]() {std::cout << "Simple Lambda fn called\n"; });
	std::jthread nonJoinable;

	// Usual way to join threads: (here: use active object instead)
	// t1.join();
	// t2.join();
	// t3.join();

	// Test active object.
	testActiveObject(t1);
	testActiveObject(t2);
	testActiveObject(t3);
	testActiveObject(nonJoinable);

	return 0;
};