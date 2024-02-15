// In this exercise, we look at the basics of a packaged tasks.
// Unlike for example threads, which take functions + arguments, it takes only a 
// function. Afterwards, it can be passed arguments to start executing.
// It also has functionality to create a future, which can get populated without
// touching the task object once the task has run (or pausing the current thread and
// forceing the task to run, too).
// Tobias Bilgeri, 3. Dec. 2023
#pragma once
#include <random>
#include <thread>
#include <chrono>
#include <future>
#include <iostream>
#include <queue>


// Thread function 
double compute(double x, double y) { 
	// Wait a while 
	// Note: the way this fct is defined, we wait exactly the same amount of time
	//       at each function call (due to reseeding with the same seed).
	//       We could make the dre and delay objects static instead.
	std::default_random_engine dre(42); 
	std::uniform_int_distribution<int> delay(0, 1000); 
	std::this_thread::sleep_for (
		std::chrono::milliseconds(delay(dre)));
	return std::cos(x) * std::exp(y); 
}


int main() {

	// Define the values to compute
	double x = 0.0;
	double y = 2.71;



	// A. 'Direct' tasks + Instant Execution
	// -------------------------------------

	// async thread: must pass function + arguments
	std::future<double> fut = std::async(compute, x, y);

	// Get the shared data
	double result = fut.get();
	std::cout << "Result: " << result << '\n';



	// B. Packaged tasks + Delayed Execution
	// -------------------------------------
	
	// packaged task: must pass function only.
	std::packaged_task<double(double, double)> task{ compute };
	std::future<double> f = task.get_future();

	// now execute the task by passing arguments (just like when we would call
	// the function).
	task(x, y);

	// future can now get the results without needing to be passed a value.
	auto res = f.get();
	std::cout << "Result: " << res << '\n';



	// C. Queued tasks + Delayed Execution
	// -----------------------------------

	std::queue<std::packaged_task<double(double, double)>> q;
	for (int i = 0; i != 10; i++) {
		q.emplace(std::packaged_task<double(double, double)> {compute});
	}

	while (!q.empty()) {
		// Note: this loop will lead to execution in sequence, since
		// each call go _future_.get() pauses the current thread until the result
		// is available.
		auto task = std::move(q.front());
		q.pop();
		task(x, y);
		auto res = task.get_future().get();
		std::cout << ("Result: " + std::to_string(res) + "\n");
	}

	return 0;
};