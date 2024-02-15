// In this exercise, we explore raw mutexes to create thread-safe programs.
// Equally, we take a look at their shortcommings, namely that they are not exception safe.
// Tobias Bilgeri, 3. Dec. 2023
#pragma once
#include "util.h"


void nonThreadSafePrintCalls() {
	// Simulate non-thread-safe print calls.
	std::cout << "\n\n -- Simulate a few non-thread-safe calls to print to terminal -- \n\n" << std::endl;

	std::string s1{ "String1" };
	std::string s2{ "String2" };
	std::string s3{ "String3" };

	std::thread t1(unsafePrintToTerminal, s1);
	std::thread t2(unsafePrintToTerminal, s2);
	std::thread t3(unsafePrintToTerminal, s3);

	t1.join();
	t2.join();
	t3.join();
}


void threadSafePrintCalls() {
	// Simulate thread-safe print calls.
	std::cout << "\n\n -- Simulate a few thread-safe calls to print to terminal -- \n\n" << std::endl;

	std::string s1{ "String1" };
	std::string s2{ "String2" };
	std::string s3{ "String3" };

	std::thread t1(threadsavePrintToTerminal, s1);
	std::thread t2(threadsavePrintToTerminal, s2);
	std::thread t3(threadsavePrintToTerminal, s3);

	t1.join();
	t2.join();
	t3.join();
}


void threadSafePrintCallsTryLock() {
	// Simulate thread-safe print calls using try_lock.
	std::cout << "\n\n -- Simulate a few thread-safe calls to print to terminal using try_lock -- \n\n" << std::endl;

	std::string s1{ "String1" };
	std::string s2{ "String2" };
	std::string s3{ "String3" };

	std::thread t1(threadsavePrintToTerminalTrylock, s1);
	std::thread t2(threadsavePrintToTerminalTrylock, s2);
	std::thread t3(threadsavePrintToTerminalTrylock, s3);

	t1.join();
	t2.join();
	t3.join();
}


int main() {

	// Run a few functions to print strings to terminal and measure function call duration:
	//  1) no lock (thread unsafe)
	//  2) lock
	//  3) try_lock + while loop
	// Durations: In my limited testing, the function with the try_lock is on average the slowest. The raw mutex and lock_guard seem similar despite the
	//            latter additionally using an RAII pattern on top of the mutex. 
	//            However, the comparison isn't very accurate, since the tasks carried out aren't exactly the same, and the order in which
	//            the functions are called matters too, with the first one being slowed down.


	// Function templated needed for my templated timer function.
	using ArglessVoidFunction = std::function<void()>;

	// Call all three versions of the printing functions and time the runtime durations.
	auto nonthreadSafeDuration = calcArglessFunctionDuration< ArglessVoidFunction>(nonThreadSafePrintCalls);
	auto threadSafeDuration = calcArglessFunctionDuration<ArglessVoidFunction>(threadSafePrintCalls);
	auto threadSafeDurationTryLock = calcArglessFunctionDuration< ArglessVoidFunction>(threadSafePrintCallsTryLock);

	// Print the resulting durations.
	std::cout
		<< "\n\nDurations: unsafe="
		<< nonthreadSafeDuration
		<< ", threadSafe="
		<< threadSafeDuration
		<< ", using try_lock="
		<< threadSafeDurationTryLock
		<< std::endl;
	

	// Simulate dead lock
	//  ... leads to a crash of the program in the end. Message displayed: [..] abort() has been callend [..]
	
	//simulateDeadlock();
	//system("pause");

	return 0;
};