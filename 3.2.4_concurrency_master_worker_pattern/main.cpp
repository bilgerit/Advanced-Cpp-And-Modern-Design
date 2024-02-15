// In this exercise, we implement a simple master-worker pattern.
// Tobias Bilgeri, 6. Dec. 2023
#pragma once
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <iostream>
#include <string>


// Global types and data needed 
std::string data;// Shared data between master and worker 
std::mutex m; // Ensures no race condition

// Synchronisation between master and worker 
std::condition_variable cv;

// Initial state of worker and master 
std::atomic<bool> workerReadyBool = false; 
std::atomic<bool> masterReadyBool = false;

// Initial state of worker and master using atomic flags
std::atomic_flag workerReadyFlag = ATOMIC_FLAG_INIT;
std::atomic_flag masterReadyFlag = ATOMIC_FLAG_INIT;


void workerThreadBool() {
	// Simple worker thread.
	// Acquires a lock, waits to be notified, processes data,
	// unlocks and notifies that the work is done.
	std::cout << "Worker (atomic bool) called.\n";

	// Lock resources when avaiable.
	std::unique_lock workerLock(m);  // can't use lock_guard here as it doesn't work with condition variables.
	std::cout << "Worker (atomic bool) acquired lock.\n";

	// Wait until worker gets called.
	cv.wait(workerLock, [] {return workerReadyBool.load(); });  // suspends the thread until workerReadyBool is true
	std::cout << "Worker (atomic bool) notified.\n";

	// Do some work
	data += " - Worker (atomic bool) - ";

	// Set master to ready.
	std::cout << "Worker (atomic bool) sets master bool to true.\n";
	masterReadyBool.store(true);

	// Unlock resources
	std::cout << "Worker (atomic bool) releasing lock.\n";
	workerLock.unlock();
	std::cout << "Worker (atomic bool) released lock.\n";

	// Notify master that work is done.
	cv.notify_one();

	std::cout << "Worker (atomic bool) exiting.\n";
}


void workerThreadFlag() {
	// Same as workerThreadBool but using the atomic flag.
	std::cout << "Worker (atomic flag) called.\n";

	// Lock resources when available.
	std::unique_lock workerLock(m);  
	std::cout << "Worker (atomic flag) acquired lock.\n";

	// Wait until worker gets called.
	cv.wait(workerLock, [] { return workerReadyFlag.test_and_set(); });
	std::cout << "Worker (atomic flag) notified.\n";

	// Do some work
	data += " - Worker (atomic flag) - ";

	// Set master to ready.
	std::cout << "Worker (atomic flag) sets master flag to true.\n";
	masterReadyFlag.test_and_set();

	// Unlock resources
	std::cout << "Worker (atomic flag) releasing lock.\n";
	workerLock.unlock();
	std::cout << "Worker (atomic flag) released lock.\n";

	// Notify master that work is done.
	cv.notify_one();

	std::cout << "Worker (atomic flag) exiting.\n";
}


void masterThreadBool() {
	// Master thread.
	// Creates worker, commands it to work, and waits for result.
	std::cout << "Master (atomic bool) called.\n";

	// Create worker thread. Worker will wait until commanded to do something.
	std::cout << "Master (atomic bool) creates worker.\n";
	std::jthread worker(workerThreadBool);

	// Create the initial data.
	std::cout << "Master (atomic bool) initializes data.\n";
	data = "Data of Master (atomic bool).";

	// Set the worker bool to ready.
	{
		std::lock_guard masterLock(m);
		std::cout << "Master (atomic bool) acquired lock.\n";
		workerReadyBool.store(true);
		std::cout << "Master (atomic bool) set worker state to ready.\n";
	}

	// Notify worker 
	std::cout << "Master (atomic bool) will notify worker.\n";
	cv.notify_one();  // wake up worker thread

	// Wait for workers to complete the job
	{
		// Wait until we are able to acquire the lock.
		std::unique_lock masterLock(m);
		std::cout << "Master (atomic bool) acquired lock. Now waiting until worker sets master state to ready\n";
		cv.wait(masterLock, [] { return masterReadyBool.load(); });
	}

	// Wait until worker is finished.
	if (worker.joinable()) {
		std::cout << "Master (atomic bool) joining the worker thread.\n";
		worker.join();
	}

	std::cout << "Master (atomic bool) exiting.\n";
}


void masterThreadFlag() {
	// Master thread.
	// Creates worker, commands it to work, and waits for result.
	std::cout << "Master (atomic flag) called.\n";

	// Create worker thread. Worker will wait until commanded to do something.
	std::cout << "Master (atomic flag) creates worker.\n";
	std::jthread worker(workerThreadFlag);

	// Create the initial data.
	std::cout << "Master (atomic flag) initializes data.\n";
	data = "Data of Master (atomic flag).";

	// Set the worker flag to ready.
	{
		std::lock_guard masterLock(m);
		std::cout << "Master (atomic flag) acquired lock.\n";
		workerReadyFlag.test_and_set();
		std::cout << "Master (atomic flag) set worker state to ready.\n";
	}

	// Notify worker
	std::cout << "Master (atomic flag) will notify worker.\n";
	cv.notify_one();

	// Wait for workers to complete the job
	{
		// Wait until we are able to acquire the lock.
		std::unique_lock masterLock(m);
		std::cout << "Master (atomic flag) acquired lock. Now waiting until worker sets master state to ready.\n";
		cv.wait(masterLock, [] { return masterReadyBool.load(); });
	}

	// Wait until worker is finished.
	if (worker.joinable()) { 
		std::cout << "Master (atomic flag) joining the worker thread.\n";
		worker.join();
	}
	std::cout << "Master (atomic flag) exiting.\n";
}


int main() {

	masterThreadBool();
	std::cout << "Result: " << data << "\n\n\n" << std::endl;

	masterThreadFlag();
	std::cout << "Result:" << data << std::endl;

	return 0;
};
