// Simple helper file containing utility needed for this exercise.
// Tobias Bilgeri, 3. Dec. 2023
#pragma once
#include <iostream>
#include <chrono>
#include <sstream>
#include <functional>
#include <thread>


// Global variable for Exercise E.
// Little bit hacky design since global variables are ideally constant,
// but it avoids me having to rewrite all the code below to support
// both options of (i) printing and (ii) not-printing the thread ID.
static bool iprint_print_thread_id{ false };


void Iprint(const std::string& s, int count) {
	// Print a string <count> number of times.
	// Interface is as demanded by the exercise (including call by
	// value for count, and not using const for count).
	std::stringstream ss;
	ss << "Iprint: ";
	for (int i = 0; i != count; i++) {
		ss << s << " ";
	}
	if (iprint_print_thread_id) {
		ss << "|| Thread ID = " << std::this_thread::get_id();
	}
	ss << "\n";
	std::cout << ss.str();
}


void iprintFreeFunc(const std::string& s, int count) {
	// Free function to call Iprint.
	Iprint(s, count);
}


auto iprintStoredLambdaFunc = [](const std::string& s, int count) -> void {
	// Stored lambda function to call Iprint.
	Iprint(s, count);
	};


struct IprintFunctor {
	// Functor to call Iprint w/ Iprint arguments defined by
	// the member variables.
	// Functor implemented as struct for brevity.
	std::string s;
	int count;
	IprintFunctor(const std::string& s, const int& count) : s(s), count(count) {};
	void operator () () const {
		Iprint(s, count);
	}
};


class IprintStaticMemberFunc {
	// Simple class w/ static iprint member function calling Iprint.
public:
	static void iprint(const std::string& s, const int& count) {
		Iprint(s, count);
	}
};


// Binded member function to call Iprint.
const auto iprintBindedMemberFunc = std::bind(
	&IprintStaticMemberFunc::iprint,
	std::placeholders::_1,
	std::placeholders::_2
);


// Exercise F: Measure time it takes to execute function:
template <typename T>
std::chrono::duration<double> functionCallTimer(std::function<T()> f) {
	// Take callable function object and measure the time it takes
	// to run it.
	// Supports callable which takes no arguments, but gives arbitrary return type.
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	// Call the function (ignore potential return type -- we have no use for it)
	f();

	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_time = end - start;
	return elapsed_time;
}
