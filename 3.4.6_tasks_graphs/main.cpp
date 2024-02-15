// In this exercise, we solve a dependency graph ...
//   a) single-threaded
//   b) multi-threaded using std::async and std::future
//   c) multi-threaded using std::promise and std::future
//   d) multi-threaded using std::packaged_task and std::future
// 
// Since the dependency-graph allows for little parallelism, the single-threaded
// solution is often fastest.
// For costly operations (on large vectors in this case), the multi-threaded
// solutions outperform.
// Generally, in my examples, the packaged_task solution seems to be the fasted
// multi-threaded solution, and often the fasted solution overall.
// 
// Tobias Bilgeri, 12. Dec. 2023
#pragma once
#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <chrono>
#include <tuple>
#include <numeric>
#include <algorithm>

// Function type concepts for generic dependency graph.
template<typename Func, typename T> concept FuncTtoT = requires(Func f, T t) {
	// Specific unary function type.
	// requires: 
	//    f(T) maps to T 
	{ f(t) } -> std::same_as<T>;
};
template<typename Func, typename T> concept FuncTTtoT = requires(Func f, T t1, T t2) {
	// Specific binary function type.
	// requires: 
	//    f(T, T) maps to T 
	{ f(t1, t2) } -> std::same_as<T>;
};

// Function for timing executions.
template<typename Func, typename... Args>
auto time_function_execution(Func f, Args... args) {
	// Time some function f of arbitrary type. 
	// Pass arguments required for f as variadic arguments.
	// Must specify template parameters for all arguments of f if it is templated.
	auto start = std::chrono::high_resolution_clock::now();
	auto res = f(args...);
	auto end = std::chrono::high_resolution_clock::now();
	return std::make_tuple(res, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
};

// Function to map vectors to string.
template <typename T>
std::string vectorToString(const std::vector<T>& vec) {
	// map a vector to a string representation.
	std::ostringstream oss;
	oss << "[";
	for (const auto& item : vec) {
		oss << item << ' ';
	}
	oss << "]";
	return oss.str();
}
// Recursive case: vector of vectors
template <typename T>
std::string vectorToString(const std::vector<std::vector<T>>& vec) {
	// map a vector of vectors to a string representation.
	std::ostringstream oss;
	for (const auto& subVec : vec) {
		oss << vectorToString(subVec) << '\n';
	}
	return oss.str();
}

// Exercise a)
template <typename T, FuncTtoT<T> Func1, FuncTtoT<T> Func2, FuncTtoT<T> Func3, FuncTTtoT<T> Func4>
T graph_single_threaded(T& input, Func1& f1, Func2& f2, Func3& f3, Func4& f4) {
	// Dependency graph for exercise a. Single-threaded.
	T b = f1(input);
	T c = f2(input);
	T d = f3(c);
	T f = f4(b, d);
	return f;
};

// Exercise b)
template <typename T, FuncTtoT<T> Func1, FuncTtoT<T> Func2, FuncTtoT<T> Func3, FuncTTtoT<T> Func4>
T graph_futures(T input, Func1& f1, Func2& f2, Func3& f3, Func4& f4) {
	// Dependency graph for exercise b. Multi-threaded using std::async and std::future.

	// Note:
	// Futures allows for a simple implementation of multi-threading since we can simply use the return values of the async threads.
	// That aside, here we need to pass <input> by value. This is because std::async will need to copy the input value into the thread.
	// That aside, here we can interestingly also specify deferred execution, and a single call to the terminal node will force all earlier threads
	// to run.

	std::future<T> b = std::async(std::launch::deferred, f1, input);
	std::future<T> c = std::async(std::launch::deferred, f2, input);
	std::future<T> d = std::async(std::launch::deferred, f3, c.get());
	std::future<T> f = std::async(std::launch::deferred, f4, b.get(), d.get());
	return f.get();
};

// Exercise c)
template <typename T, FuncTtoT<T> Func1, FuncTtoT<T> Func2, FuncTtoT<T> Func3, FuncTTtoT<T> Func4>
T graph_promises(T& input, Func1& f1, Func2& f2, Func3& f3, Func4& f4) {
	// Dependency graph for exercise c. Multi-threaded using std::promise and std::future.

	// Note:
	// This is a bit more verbose than using futures only, since we need to create promise types first, then get the futures, and then
	// create the threads with lambda functions that capture and lateron set the values of the promise types.

	// Declare promise types.
	std::promise<T> b;
	std::promise<T> c;
	std::promise<T> d;
	std::promise<T> f;

	// Get promise-associated futures.
	std::future<T> b_f = b.get_future();
	std::future<T> c_f = c.get_future();
	std::future<T> d_f = d.get_future();
	std::future<T> f_f = f.get_future();

	// Create threads using Lambda-functions.
	// The lambda-functions caputure [promise, fct, fct_args] and compute the promise value via promise.set_value(fct(fct_args)).
	std::thread t1([&b, &f1, &input]() { b.set_value(f1(input)); });
	std::thread t2([&c, &f2, &input]() { c.set_value(f2(input)); });
	std::thread t3([&d, &f3, &c_f]() { d.set_value(f3(c_f.get())); });
	std::thread t4([&f, &f4, &b_f, &d_f]() { f.set_value(f4(b_f.get(), d_f.get())); });
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	return f_f.get();
};

// Exercise d)
template <typename T, FuncTtoT<T> Func1, FuncTtoT<T> Func2, FuncTtoT<T> Func3, FuncTTtoT<T> Func4>
T graph_packaged_task(T& input, Func1& f1, Func2& f2, Func3& f3, Func4& f4) {
	// Dependency graph for exercise d. Multi-threaded using std::packaged_task and std::future.

	// Note:
	// This is again a bit more verbose than using futures only, since we need to create packaged_task types first, then get the futures, and then
	// call the packaged tasks. Still, it is less verbose than using promise-types.

	// Create the packaged tasks.
	std::packaged_task<T(T)> b(f1);
	std::packaged_task<T(T)> c(f2);
	std::packaged_task<T(T)> d(f3);
	std::packaged_task<T(T, T)> f(f4);

	// Fetch packaged_task-associated futures.
	std::future<T> b_f = b.get_future();
	std::future<T> c_f = c.get_future();
	std::future<T> d_f = d.get_future();
	std::future<T> f_f = f.get_future();

	// Call the packaged tasks.
	b(input);
	c(input);
	d(c_f.get());
	f(b_f.get(), d_f.get());

	return f_f.get();
};

int main() {

	{
		// Example: Integer type and simple arithmetic operations.
		int input = 1;
		auto f1 = [](const int& x) { return x + 1; };
		auto f2 = [](const int& x) { return x + 1; };
		auto f3 = [](const int& x) { return x + 1; };
		auto f4 = [](const int& x, const int& y) { return x + y; };

		auto [res_a, duration_a] = time_function_execution(graph_single_threaded<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_b, duration_b] = time_function_execution(graph_futures<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_c, duration_c] = time_function_execution(graph_promises<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_d, duration_d] = time_function_execution(graph_packaged_task<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);

		std::cout
			<< "Example 1: simple integer arithmetics. Results:"
			<< "\n\tsingle_thread: res=" << res_a << ", duration=" << duration_a << "us, "
			<< "\n\tfutures: res=" << res_b << ", duration=" << duration_b << "us, "
			<< "\n\tpromise: ress=" << res_c << ", duration=" << duration_c << "us, "
			<< "\n\tpackaged_task: res=" << res_d << ", duration=" << duration_d << "us"
			<< std::endl;
	}

	{
		// Example: Double type and slightly more complex arithmetic operations.
		double input = 5.;
		auto f1 = [](const double& x) { return log(x); };
		auto f2 = [](const double& x) { return exp(x); };
		auto f3 = [](const double& x) { return x + 1; };
		auto f4 = [](const double& x, const double& y) { return log(x + y - 1); };

		auto [res_a, duration_a] = time_function_execution(graph_single_threaded<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_b, duration_b] = time_function_execution(graph_futures<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_c, duration_c] = time_function_execution(graph_promises<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_d, duration_d] = time_function_execution(graph_packaged_task<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);

		std::cout
			<< "\n\nExample 2: floating point arithmetics. Results: "
			<< "\n\tsingle_thread: res=" << res_a << ", duration=" << duration_a << "us, "
			<< "\n\tfutures: res=" << res_b << ", duration=" << duration_b << "us, "
			<< "\n\tpromises: res=" << res_c << ", duration=" << duration_c << "us, "
			<< "\n\tpackaged_task: res=" << res_d << ", duration=" << duration_d << "us"
			<< std::endl;
	}

	{
		// Example: Vector.
		std::vector<double> input = { 1., 2., 3., 4., 5. };
		auto f1 = [](std::vector<double> x) {
			std::for_each(x.begin(), x.end(), [](double& x) {
				x = log(x); });
			return x;
			};
		auto f2 = [](std::vector<double> x) {
			std::for_each(x.begin(), x.end(), [](double& x) {
				x = exp(x); });
			return x;
			};
		auto f3 = [](std::vector<double> x) {
			std::for_each(x.begin(), x.end(), [](double& x) {
				x = x + 1; });
			return x;
			};
		auto f4 = [](std::vector<double> x, std::vector<double> y) {
			std::vector<double> res(x.size());
			std::transform(x.begin(), x.end(), y.begin(), res.begin(), [](double x, double y) { return log(x + y - 1); });
			return res;
			};

		auto [res_a, duration_a] = time_function_execution(graph_single_threaded<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_b, duration_b] = time_function_execution(graph_futures<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_c, duration_c] = time_function_execution(graph_promises<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_d, duration_d] = time_function_execution(graph_packaged_task<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);

		std::cout
			<< "\n\nExample 3: Small vector. Results: "
			<< "\n\tsingle_thread: res=" << vectorToString(res_a) << ", duration=" << duration_a << "us, "
			<< "\n\tfutures: res=" << vectorToString(res_b) << ", duration=" << duration_b << "us, "
			<< "\n\tpromises: res=" << vectorToString(res_c) << ", duration=" << duration_c << "us, "
			<< "\n\tpackaged_task: res=" << vectorToString(res_d) << ", duration=" << duration_d << "us"
			<< std::endl;
	}

	{
		// Example: Large Vector.
		std::vector<double> input(10'000'000, 1);
		// Make each element unique: 1, 2, 3, ...
		std::for_each(input.begin(), input.end(), [i = 0](double& x) mutable { x += i; i += 1; });

		auto f1 = [](std::vector<double> x) {
			std::for_each(x.begin(), x.end(), [](double& x) {
				x = log(x); });
			return x;
			};
		auto f2 = [](std::vector<double> x) {
			std::for_each(x.begin(), x.end(), [](double& x) {
				x = exp(x); });
			return x;
			};
		auto f3 = [](std::vector<double> x) {
			std::for_each(x.begin(), x.end(), [](double& x) {
				x = x + 1; });
			return x;
			};
		auto f4 = [](std::vector<double> x, std::vector<double> y) {
			std::vector<double> res(x.size());
			std::transform(x.begin(), x.end(), y.begin(), res.begin(), [](double x, double y) { return log(x + y - 1); });
			return res;
			};

		auto [res_a, duration_a] = time_function_execution(graph_single_threaded<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_b, duration_b] = time_function_execution(graph_futures<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_c, duration_c] = time_function_execution(graph_promises<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_d, duration_d] = time_function_execution(graph_packaged_task<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);

		std::cout
			<< "\n\nExample 4: large vector. Results: "
			<< "\n\tsingle_thread: duration=" << duration_a << "us, "
			<< "\n\tfutures: duration=" << duration_b << "us, "
			<< "\n\tpromises: duration=" << duration_c << "us, "
			<< "\n\tpackaged_task: duration=" << duration_d << "us"
			<< std::endl;
	}

	{
		// Example 5: Matrix // Vector of vectors.
		std::vector<std::vector<double>> input(5, std::vector<double>(5, 1));
		// Make each element unique: 1, 2, 3, ...
		int i = 0;
		for (auto& row : input) {
			std::for_each(row.begin(), row.end(), [i](double& x) mutable { x += i; i += 1; });
		}

		auto f1 = [](std::vector<std::vector<double>> x) {
			for (auto& row : x) {
				std::for_each(row.begin(), row.end(), [](double& x) {
					x = log(x); });
			}
			return x;
			};
		auto f2 = [](std::vector<std::vector<double>> x) {
			for (auto& row : x) {
				std::for_each(row.begin(), row.end(), [](double& x) {
					x = exp(x); });
			}
			return x;
			};
		auto f3 = [](std::vector<std::vector<double>> x) {
			for (auto& row : x) {
				std::for_each(row.begin(), row.end(), [](double& x) {
					x = x + 1; });
			}
			return x;
			};
		auto f4 = [](std::vector<std::vector<double>> x, std::vector<std::vector<double>> y) {
			std::vector<std::vector<double>> res(x.size(), std::vector<double>(x[0].size()));
			for (size_t i = 0; i < x.size(); ++i) {
				std::transform(x[i].begin(), x[i].end(), y[i].begin(), res[i].begin(), [](double x, double y) { return log(x + y - 1); });
			}
			return res;
			};

		auto [res_a, duration_a] = time_function_execution(graph_single_threaded<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_b, duration_b] = time_function_execution(graph_futures<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_c, duration_c] = time_function_execution(graph_promises<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);
		auto [res_d, duration_d] = time_function_execution(graph_packaged_task<decltype(input), decltype(f1), decltype(f2), decltype(f3), decltype(f4)>, input, f1, f2, f3, f4);

		std::cout
			<< "\n\nExample 5: matrix. Results: "
			<< "\n\tsingle_thread: duration=" << duration_a << "us, "
			<< "\n\tfutures: duration=" << duration_b << "us, "
			<< "\n\tpromises: duration=" << duration_c << "us, "
			<< "\n\tpackaged_task: duration=" << duration_d << "us"
			<< std::endl;
	}

	return 0;
};
