// Simple helper file contains the timing and printing functions needed for this exercise.
// The printing functions are implented non-thread-safe, thread-safe via a raw mutex, and thread-safe via a raw mutex using a while-loop and try_lock() method.
// Tobias Bilgeri, 3. Dec. 2023
#pragma once
#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <functional>
#include <chrono>
#include <mutex>


// Define global mutex. Note that this is not exception safe. In practice, use for example a lock guard.
std::mutex m;


template<typename ArglessFunction>
auto calcArglessFunctionDuration(const ArglessFunction& f) {
	// Measure time to run of some argument-free function.
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> end;
	start = std::chrono::system_clock::now();
	f();
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> duration = end - start;
	return duration;
}


void unsafePrintToTerminal(const std::string& s) {
	// Simluate a non-thread-safe print call.
	std::cout << "Thread " << "Unsafe: " << s << std::endl;
}



void threadsavePrintToTerminal(const std::string& s) {
	// Print a string to terminal.
	// Uses a mutex to be thread safe.
	// Mutex is used in a raw manner, meaning that this function is not exception safe.
	m.lock();
	std::cout << "Thread " << "Safe: " << s << std::endl;
	m.unlock();
}


void threadsavePrintToTerminalTrylock(const std::string& s) {
	// Print a string to terminal.
	// Uses a mutex to be thread safe.
	// Mutex is used in a raw manner, meaning that this function is not exception safe.
	// Additionally, count the amount of times we call try_lock before succeeding.
	int trylockAttempts{ 0 };
	while (true) {
		if (m.try_lock()) {
			std::cout << "Thread Safe: " << s << " || try_lock() attempts: " << trylockAttempts << std::endl;
			m.unlock();
			return;
		}
		else {
			// If thread can't lock the mutex: increment counter and try again.
			// Note that in pracice we might add a sleep statement below, but here we want to see 
			// full number of attempts if no sleep is present.
			trylockAttempts++;
		}
	}
}



void simulateDeadlock() {
	// Simulate a deadlock by throwing an exception prior to calling unlock.
	try {
		m.lock();
		std::cout << "About to create a deadlock!" << std::endl;
		throw std::bad_function_call();
		m.unlock();
	}
	catch (std::bad_function_call& e) {
		std::cout << "Succesfully created a deadlock! Error thrown: " << e.what() << std::endl;
	}
}

