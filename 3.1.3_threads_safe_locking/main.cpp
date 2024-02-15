// In this exercise, we take a closer look at unique locks, an RAII style handler of mutexes.
// We use them to automatically unlock mutexes when the unique locks go out of scopes,
// explore instantaneous vs delayed locking, timed mutexes and locking via try_for,
// and various ways of error handling around locks. 
// Tobias Bilgeri, 3. Dec. 2023
#pragma once
#include "util.h"
#include <tuple>


void printLockViaRawMutex() {
	// Simulate thread-safe print calls making use of a mutex.
	std::cout << "\n\n -- Simulate a few thread-safe calls to print to terminal using mutex -- \n\n" << std::endl;

	std::string s1{ "String1" };
	std::string s2{ "String2" };
	std::string s3{ "String3" };
	std::string s4{ "String4" };

	std::thread t1(lockViaRawMutex, s1);
	std::thread t2(lockViaRawMutex, s2);
	std::thread t3(lockViaRawMutex, s3);
	std::thread t4(lockViaRawMutex, s4);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}


void printLockViaRawMut() {
	// Simulate thread-safe print calls making use of a lock guard.
	std::cout << "\n\n -- Simulate a few thread-safe calls to print to terminal using lock guard -- \n\n" << std::endl;

	std::string s1{ "String1" };
	std::string s2{ "String2" };
	std::string s3{ "String3" };
	std::string s4{ "String4" };

	std::thread t1(lockViaLockGuard, s1);
	std::thread t2(lockViaLockGuard, s2);
	std::thread t3(lockViaLockGuard, s3);
	std::thread t4(lockViaLockGuard, s4);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}


void printLockViaUniqueLock() {
	// Simulate thread-safe print calls making use of a unique lock.
	std::cout << "\n\n -- Simulate a few thread-safe calls to print to terminal using unique lock -- \n\n" << std::endl;

	std::string s1{ "String1" };
	std::string s2{ "String2" };
	std::string s3{ "String3" };
	std::string s4{ "String4" };

	std::thread t1(lockViaUniqueLock, s1);
	std::thread t2(lockViaUniqueLock, s2);
	std::thread t3(lockViaUniqueLock, s3);
	std::thread t4(lockViaUniqueLock, s4);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}



int main() {

	// Questions A - B

	// Timed calls to print to terminal using (i) raw mutex (ii) lock guard (iii) unique_lock
	// Interestingly, in this simple test, the lock guard is consistently faster than the raw mutex (same for unique_lock). 
	// However, this seems to be mostly due to the order in which the code is called,
	// see: stackoverflow.com/questions/59256132/how-can-stdlock-guard-be-faster-than-stdmutexlock
	// If I swap the order in which the functions are called, the raw mutex becomes faster.
	// A better comparison would be to run the two programms seperately, as well as to look at the assembly code the compiler creates.
	auto durationRawMutex = calcArglessFunctionDuration<std::function<void()>>(printLockViaRawMut);
	auto durationLockGuard = calcArglessFunctionDuration<std::function<void()>>(printLockViaRawMutex);
	auto durationUniqueLock = calcArglessFunctionDuration<std::function<void()>>(printLockViaUniqueLock);

	std::cout
		<< "\n\nDurations: raw mutex="
		<< durationRawMutex
		<< ", lock guard="
		<< durationLockGuard
		<< ", unique lock="
		<< durationUniqueLock
		<< std::endl;



	// Question C
	// Unique locks w/ exception handling in case we can't lock or mutex not assigned to lock.
	std::cout << "\n\n" << std::endl;

	// One of these will throw a (handled) exception: deadlock occurs.
	std::jthread t1(uniqueLockWithExceptionHandling);
	std::jthread t2(uniqueLockWithExceptionHandling);
	t1.join();
	t2.join();

	// Can print again after above threads ran:
	uniqueLockWithExceptionHandling();

	// Simple demonstration of exception handling for the lock w/o assigned mtuex:
	noAssociatedLockErrorDemonstration();



	// Question D
	// Same as C but each lock tries to lock for a specific duration (microseconds) until it
	// gives up.

	// Three threads of which 2 don't wait, while one waits for up to a second.
	// Most likely scenario:
	// Two threads will find the console blocked. One will wait, the other one throw a (handled)
	// exception.
	std::jthread tf1(uniqueLockWithExceptionHandlingTryFor, 0);
	std::jthread tf2(uniqueLockWithExceptionHandlingTryFor, 0);
	std::jthread tf3(uniqueLockWithExceptionHandlingTryFor, 1000000);
	tf1.join();
	tf2.join();
	tf3.join();



	// Question E
	std::cout << "\n\n" << std::endl;

	// Successful manual locking and unlocking.
	std::unique_lock ulock1{ console_timed, std::defer_lock };
	ulock1.lock();
	ulock1.unlock();
	std::cout << "Ex. E: Successful manual lock and unlock. " << std::endl;

	// Unlocking a non-locked mutex.
	// Error code is same as when trying to lock a lock w/o associated mutex (op. not permitted)
	try { ulock1.unlock(); }
	catch (const std::system_error& e) {
		if (e.code() == std::errc::operation_not_permitted) {
			std::cout << "Ex. E: Caught expected exception for trying to unlock a non-locked mutex: " << e.what() << std::endl;
		}
		else {
			std::cout << "Ex. E: Unexpected exception: " << e.what() << std::endl;
		}
	}



	// Question F
	// Same as Question D but using try_lock_until
	std::cout << "\n\n" << std::endl;

	std::jthread tu1(uniqueLockWithExceptionHandlingTryUntil, 0);
	std::jthread tu2(uniqueLockWithExceptionHandlingTryUntil, 0);
	std::jthread tu3(uniqueLockWithExceptionHandlingTryUntil, 1000000);
	tu1.join();
	tu2.join();
	tu3.join();


	// Question G
	std::cout << "\n\n" << std::endl;

	// Create unique lock and make sure mutex is locked.
	std::unique_lock gLock(console, std::defer_lock);
	if (gLock.try_lock()){
		std::cout << "Ex. G. Mutex is now locked" << std::endl;
	}

	// Release mutex from lock
	gLock.release();

	// unique lock now holds nullptr as mutex
	if (gLock.mutex() == nullptr) {
		std::cout << "Ex. G. Mutex has been released from lock!" << std::endl;
	}

	// try locking mutex -- it should still be locked
	if (!console.try_lock()) {
		std::cout << "Ex. G. Mutex is still locked!" << std::endl;
	}

	// Unlock the mutex directly.
	console.unlock();

	return 0;
};
