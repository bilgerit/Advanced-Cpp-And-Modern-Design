// In this exercise, we take a first look at atomics.
// std::atomic<T> come with various member functions such as .load(), .store(), .is_lock_free(), etc.
// Atomics also support plain assignements such as atomic_object=my_literal.
// Tobias Bilgeri, 6. Dec. 2023
#pragma once
#include <atomic>
#include <iostream>


int main() {
	
	// Define Atomics
	std::atomic<long long> aLongLong;
	std::atomic<bool> aBool;
	std::atomic<int> aInt;
	std::atomic<int> aInt2;

	// Check if they are lock free
	std::cout << "Atomic long long: is lock free=" << std::boolalpha << aLongLong.is_lock_free() << std::endl;
	std::cout << "Atomic bool: is lock free=" << std::boolalpha << aBool.is_lock_free() << std::endl;
	std::cout << "Atomic int: is lock free=" << std::boolalpha << aInt.is_lock_free() << std::endl;
	// Note: Alternative syntax: std::atomic_is_lock_free(&aLongLong)

	// Store some values
	aLongLong.store(2);
	aBool.store(false);
	aInt.store(1);
	aInt2.store(2);

	// Atomically replace the value of one atomic object by another atomic object.
	std::cout << "\n\nAtomically stored values PRIOR to replacement: val1=" << aInt.load() << ", val2=" << aInt2.load() << std::endl;
	aInt.store(aInt2.load());
	std::cout << "Atomically stored values AFTER to replacement: val1=" << aInt.load() << ", val2=" << aInt2.load() << std::endl;
	// Note: Can also do plain assignements: aInt = 10;
	
	// Atomically load an atomic object and return its current value.
	std::cout << "\n\nLoad atomic object and return it's current value: " << aInt2.load() << std::endl;

	return 0;
};