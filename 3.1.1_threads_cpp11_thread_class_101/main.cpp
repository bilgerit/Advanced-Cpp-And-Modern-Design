// In this exercise, we look at the basics of multithreading using std::thread.
// 1) creating threads (std::thread(_callable_, _arg1_, _arg2_, ...)
// 2) joining and detaching (.join(), .detach())
// 3) monitoring threads via std::this_thread::get_id() and _thread_object.get_id()
// 4) proper handling using _thread_object_.is_joinable() and try/catch blocks
// 5) monitor some effects of concurrency, such as 
//     - mix-ups in the order with which elements get printed to console via 
//       std::cout << .. << std::endl,
//     - changes in execution speed (concurrency gains vs overhead when creating 
//       threads) monitored with std::chrono
// Tobias Bilgeri, 3. Dec. 2023
#pragma once
#include "util.h"
#include <stdexcept>


int ex_a() {
	// a) Create as many callable objects as you can (free functions, 
	// lambda function and stored lambda function, function object, 
	// binded member function, static member function) that all call 
	// the interface Iprint above.

	std::cout << "\n\nExercise A\n\nTest all functions\n" << std::endl;

	iprintFreeFunc("FreeFunction", 1);

	iprintStoredLambdaFunc("StoredLambda", 2);

	IprintFunctor iprint_functor("Functor", 3);
	iprint_functor();

	IprintStaticMemberFunc::iprint("StaticMemFunc", 4);

	iprintBindedMemberFunc("BindedFunc", 5);

	// Note: non-stored lambda doesn't really make sense here and will
	//       be used in exercise b.

	return 0;
};


int ex_b() {
	// b) Create a thread for each of the callable objects in part a). 
	// One of the threads should be a detached thread. Each thread’s 
	// function has its own unique ID.

	std::cout
		<< "\n\nExercise B\n\n"
		<< "Creating 6 threads, printing their unique IDs, then call "
		".join() on 5 of them. \nFor the free function, we will call "
		".detach() instead. \nNote that the printing order will "
		"be mixed up, as std::cout << is not thread safe!\n"
		"(I left this non-safe behaviour in on purpose.)\n"
		<< std::endl;

	// Create all threads:
	IprintFunctor iprint_functor("Functor", 1);

	std::thread t1(iprintFreeFunc, "FreeFunction", 1);
	std::thread t2(iprintStoredLambdaFunc, "StoredLambda", 1);
	std::thread t3(iprint_functor);
	std::thread t4(IprintStaticMemberFunc::iprint, "StaticMemFunc", 1);
	std::thread t5(iprintBindedMemberFunc, "BindedFunc", 1);
	std::thread t6(
		[](const std::string& s, const int& count) { Iprint(s, count); },
		"NonStoredLambda",
		1
	);


	// Print the IDs
	// (std::cout << and std::endlis not thread safe ... I left it in on purpose
	//  as a demonstration of what can happen when doing concurrency
	//  poorly! Good practice is to end lines with \n instead of endl,
	//  and assemble lines to be printed via stringstream rather than
	//  multiple usages of the << operator).
	std::cout << "Thread #1 ID: " << t1.get_id() << std::endl;
	std::cout << "Thread #2 ID: " << t2.get_id() << std::endl;
	std::cout << "Thread #3 ID: " << t3.get_id() << std::endl;
	std::cout << "Thread #4 ID: " << t4.get_id() << std::endl;
	std::cout << "Thread #5 ID: " << t5.get_id() << std::endl;
	std::cout << "Thread #6 ID: " << t6.get_id() << std::endl;


	// Calling .join():
	// Blocks the main threat until all threats on which we called
	// join in this scope are completed.

	// Calling.detach():
	// When a thread object goes out of scope, it will call std::terminate
	// unless we called .join() or .detach().
	// Calling .join() means we wait for it's completion while blocking current thread.
	// Calling .detach() means we will not wait and the thread can
	// continue running in the background.
	// This possibly leads to unwanted behaviour and is usually not
	// recomended.
	// Source: see for example this and therein linked threads:
	// stackoverflow.com/questions/22803600/when-should-i-use-

	t1.detach();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();

	return 0;
};


int ex_c_d() {
	// c) Introduce code to check if threads have completed and then 
	// join each one if this is the case.
	// d) We need to introduce exception handling in the case that a 
	// thread may not be joined. In these cases we need to introduce 
	// join() inside the catch blocks.

	std::cout
		<< "\n\nExercise C & D\n\nUse .joinable() and try/catch blocks for .join()\n"
		<< std::endl;

	// ================================================================
	// ================================================================
	// ================================================================
	// Same code as in Exercise B to create all threads:
	IprintFunctor iprint_functor("Functor", 1);

	std::thread t1(iprintFreeFunc, "FreeFunction", 1);
	std::thread t2(iprintStoredLambdaFunc, "StoredLambda", 1);
	std::thread t3(iprint_functor);
	std::thread t4(IprintStaticMemberFunc::iprint, "StaticMemFunc", 1);
	std::thread t5(iprintBindedMemberFunc, "BindedFunc", 1);
	std::thread t6(
		[](const std::string& s, const int& count) { Iprint(s, count); },
		"NonStoredLambda",
		1
	);
	// ================================================================
	// ================================================================
	// ================================================================

	// For each thread:
	//  - Check if it is joinable (false if thread is default constructed,
	//    or thread already was joined, or thread was detached, see
	//    cppreference.com/w/cpp/thread/thread/joinable)
	//  - Call .join() within a try/catch block so when a thread can
	//    not be joined(), the exception is handled appropriately.

	if (t1.joinable()) {
		try {
			t1.join();

			// Dummy throw
			//throw std::bad_function_call();
		}
		catch (...) {
			std::stringstream s1;
			s1 << "Thread not joinable. ID=" << t1.get_id();
			std::cout << s1.str();
			// (Better would be: catch specific condition, e.g. std::system_error)
		};
	}

	if (t2.joinable()) {
		try {
			t2.join();
		}
		catch (...) {
		};
	}

	if (t3.joinable()) {
		try {
			t3.join();
		}
		catch (...) {
		};
	}

	if (t4.joinable()) {
		try {
			t4.join();
		}
		catch (...) {
		};
	}

	if (t5.joinable()) {
		try {
			t5.join();
		}
		catch (...) {
		};
	}

	if (t6.joinable()) {
		try {
			t6.join();
		}
		catch (...) {
		};
	}

	return 0;
};


int ex_e() {
	// e) Print the thread ID of each thread in each implementation of 
	// Iprint.

	std::cout << "\n\nExercise E\n\nPrint all thread IDs\n" << std::endl;

	// Setting this global variable to true makes us print the thread ID in Iprint.
	iprint_print_thread_id = true;

	// ================================================================
	// ================================================================
	// ================================================================
	// Same code as in Exercises C & D to create and join all threads:
	IprintFunctor iprint_functor("Functor", 1);

	std::thread t1(iprintFreeFunc, "FreeFunction", 1);
	std::thread t2(iprintStoredLambdaFunc, "StoredLambda", 1);
	std::thread t3(iprint_functor);
	std::thread t4(IprintStaticMemberFunc::iprint, "StaticMemFunc", 1);
	std::thread t5(iprintBindedMemberFunc, "BindedFunc", 1);
	std::thread t6(
		[](const std::string& s, const int& count) { Iprint(s, count); },
		"NonStoredLambda",
		1
	);

	if (t1.joinable()) {
		try {
			t1.join();
		}
		catch (...) {
		};
	}

	if (t2.joinable()) {
		try {
			t2.join();
		}
		catch (...) {
		};
	}

	if (t3.joinable()) {
		try {
			t3.join();
		}
		catch (...) {
		};
	}

	if (t4.joinable()) {
		try {
			t4.join();
		}
		catch (...) {
		};
	}

	if (t5.joinable()) {
		try {
			t5.join();
		}
		catch (...) {
		};
	}

	if (t6.joinable()) {
		try {
			t6.join();
		}
		catch (...) {
		};
	}
	// ================================================================
	// ================================================================
	// ================================================================

	iprint_print_thread_id = false;

	return 0;
}


int ex_f() {
	// f) Compute the running time of the program based on the example 
	// code in the summary based on std::chrono.

	// Here I simply measure the time it took to run Exercise A vs B.
	// B is clearly slower on my machine.
	// On my machine, about 80% of the overhead are due to the additional
	// printing of the thread IDs in exercise B (I tested this by just
	// commenting out the relevant printing statements).
	// The rest of the overhead is the overhead due to us creating
	// additional threads for very simple tasks, where the thread-
	// creation overhead dominates over the concurrency benefits.

	std::cout << "\n\nExercise F\n\n" << std::endl;

	std::cout << "\n\nCompute time it took to run Exercise A\n\n" << std::endl;
	auto execution_time_a = functionCallTimer<int>(ex_a);

	std::cout << "\n\n\n\nCompute time it took to run Exercise B\n\n" << std::endl;
	auto execution_time_b = functionCallTimer<int>(ex_b);

	std::cout
		<< "\n\nTime it took to run Exercise A: "
		<< execution_time_a
		<< "\nTime it took to run Exercise B: "
		<< execution_time_b
		<< std::endl;

	return 0;
}


int main() {

	ex_a();
	ex_b();
	ex_c_d();
	ex_e();
	ex_f();

	return 0;
};