// Simple helper file containing utility needed for this exercise.
// Mostly, we test different ways to lock the console, delayed locking, 
// and error handling around locks and mutexes.
// Tobias Bilgeri, 3. Dec. 2023
#pragma once
#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <functional>
#include <chrono>
#include <mutex>


// raw mutex
std::mutex console;
std::timed_mutex console_timed;


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


void lockViaRawMutex(const std::string& s) {
	// Print a string to console.
	// Uses a mutex to be thread safe.
	// Mutex is used in a raw manner, meaning that this function is not exception safe.
	console.lock();
	std::cout << "Thread " << "Safe (via mutex): " << s << std::endl;
	console.unlock();
}


void lockViaLockGuard(const std::string& s) {
	// Print a string to console.
	// Uses a mutex to be thread safe.
	// Mutex is used via a lock guard, which automatically unlocks via it's destructor even if the function is existed prematurely for whatever reason (exception, return statement).
	// lock_guard is a typical RAII pattern (like smart pointers, RAII file handlers, etc.)
	const std::lock_guard lock(console);
	std::cout << "Thread " << "Safe (via lock guard): " << s << std::endl;
}


void lockViaUniqueLock(const std::string& s) {
	// Print a string to console.
	// Uses a mutex to be thread safe.
	// Mutex is used via a unique lock, which is similar to lock_guard, but more flexible, allowing for:
	// deferred locking, time-constrained attempts at locking, recursive locking, transfer of lock ownership, and use with condition variables.

	// When creating the unique lock: can use multiple 'lock tags': std::defer_lock, std::try_to_lock, std::adopt_lock
	// (see https://en.cppreference.com/w/cpp/thread/lock_tag)
	const auto lock_tag = std::defer_lock;
	std::unique_lock lock{ console, lock_tag };
	lock.lock();
	std::cout << "Thread " << "Safe (via lock guard): " << s << std::endl;
}


// Exercise C -- function implementation
void uniqueLockWithExceptionHandling() {
	// Locking the console using unique_lock with try_lock and error handling in case
	// the console can't be locked when trying for the first time.

	// Exception handling: No associated lock
	//    If I use std::unique_lock<std::mutex> l; l.lock();  ... I will get this exception,
	//    since I never provided a mutex for the unique_lock to work with.
	// 
	// Exception handling: Already locked
	//    Self explanatory

	std::unique_lock lock{ console, std::defer_lock };
	try {
		if (lock.try_lock()) {
			std::cout << "Ex. C. Succesfully locked. " << std::endl;
		}
		else {
			throw std::system_error(
				std::make_error_code(
					std::errc::resource_deadlock_would_occur
				)
			);
		}
	}
	catch (const std::system_error& e) {
		if ((e.code() == std::make_error_code(std::errc::operation_not_permitted)) ||  // no associated mutex
			(e.code() == std::make_error_code(std::errc::resource_deadlock_would_occur))  // already locked
			) {
			std::cout << "Ex. C. Expected exception caught: " << e.what() << std::endl;
		}
		else {
			std::cout << "Ex. C. Unexpected exception caught: " << e.code() << std::endl;
		}
	}
}


void noAssociatedLockErrorDemonstration() {
	// Quick demonstration of the error obtained when having no associated mutex.
	std::unique_lock<std::mutex> lock;  // no mutex provided to lock via e.g. constructor
	try {
		if (!lock.try_lock()) {
			throw std::system_error(
				std::make_error_code(
					std::errc::resource_deadlock_would_occur
				)
			);
		}
	}
	catch (const std::system_error& e) {
		if (e.code() == std::make_error_code(std::errc::operation_not_permitted)) {  // no associated mutex
				std::cout << "Ex. C. Expected exception caught: " << e.what() << std::endl;
		}
		else {
			std::cout << "Ex. C. Unexpected exception caught: " << e.code() << std::endl;
		}
	}
}


// Exercise D -- function implementation
void uniqueLockWithExceptionHandlingTryFor(const int& try_lock_for_micros) {
	// Locking the console using unique_lock with try_lock_for and error handling in case
	// the console can't be locked when trying for a period of time.
	// Same as in exercise C except that we try to lock for a finite duration rather than
	// only at a single point in time.
	std::unique_lock lock{ console_timed, std::defer_lock };
	try {
		if (lock.try_lock_for(std::chrono::microseconds(try_lock_for_micros))) {
			std::cout << "Ex. D. Succesfully locked. " << std::endl;
		}
		else {
			throw std::system_error(
				std::make_error_code(
					std::errc::resource_deadlock_would_occur
				)
			);
		}
	}
	catch (const std::system_error& e) {
		if ((e.code() == std::make_error_code(std::errc::operation_not_permitted)) ||  // no associated mutex
			(e.code() == std::make_error_code(std::errc::resource_deadlock_would_occur))  // already locked
			) {
			std::cout << "Ex. D. Expected exception caught: " << e.what() << std::endl;
		}
		else {
			std::cout << "Ex. D. Unexpected exception caught: " << e.code() << std::endl;
		}
	}
}


// Exercise F -- function implementation
// Same as for Ex. D but using try_lock_until
void uniqueLockWithExceptionHandlingTryUntil(const int& try_lock_duration_micros) {
	// Locking the console using unique_lock with try_lock_until and error handling in case
	// the console can't be locked when trying for a period of time.
	std::unique_lock lock{ console_timed, std::defer_lock };
	try {
		if (lock.try_lock_until(std::chrono::system_clock::now() + std::chrono::microseconds(try_lock_duration_micros))) {
			std::cout << "Ex. F. Succesfully locked. " << std::endl;
		}
		else {
			throw std::system_error(
				std::make_error_code(
					std::errc::resource_deadlock_would_occur
				)
			);
		}
	}
	catch (const std::system_error& e) {
		if ((e.code() == std::make_error_code(std::errc::operation_not_permitted)) ||  // no associated mutex
			(e.code() == std::make_error_code(std::errc::resource_deadlock_would_occur))  // already locked
			) {
			std::cout << "Ex. F. Expected exception caught: " << e.what() << std::endl;
		}
		else {
			std::cout << "Ex. F. Unexpected exception caught: " << e.code() << std::endl;
		}
	}
}

