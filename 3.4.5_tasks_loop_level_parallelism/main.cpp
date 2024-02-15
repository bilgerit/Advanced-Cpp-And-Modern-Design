// In this exercise, we compare various methods to perform operations on vectors.
// 
// SUM (testing std & custom algos):
//  - Single-threaded std::accumulate: relatively performant if the other methods aren't optimized.
//  - Parallel std::reduce: performs best in this example.
//  - Recusively splitting the array, tasks: slow when using the demanded 1e3 elements cutoff (due to overhead of creating threads and the many function calls), rather fast if the cutoff is ~ 1e5.
//               Note that deferred execution is a bit faster than immediate execution, as discussed here: stackoverflow.com/questions/67034861/why-would-concurrency-using-stdasync-be-faster-than-using-stdthread
//  - Open MP: Not faster in my example even if I increase the number of threads. In this case, the overhead of creating the threads is too large.
//  - Recusively splitting the array, threads: similar performance to tasks (a bit slower here). Other people have also observed this for simple implementations (see e.g. stackoverflow.com/questions/67034861/why-would-concurrency-using-stdasync-be-faster-than-using-stdthread).
//               Similar to tasks, using a cutoff of ~ 2e5 elements is much faster than using 1e3 elements.
//   CONCLUSION: std::reduce seems to be optimal here.
// 
// TRANSFORM / SORT / FIND (std algos only):
//   CONCLUSION: single-threaded std algos are slower than multi-threaded std algos in this example. 
// 
// Tobias Bilgeri, 12. Dec. 2023
#pragma once
#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <thread>
#include <future>
#include <algorithm>
#include <execution>
#include <omp.h>

using namespace std::chrono;

const int numElementsLarge = 1'000'000;

// Part a)
void part_a() {
    // Simple non-concurrent sum using std::accumulate
    std::vector<int> v(numElementsLarge, 1);
    auto start = high_resolution_clock::now();
    int sum = std::accumulate(v.begin(), v.end(), 0);
    auto end = high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Ex. A. Time it took to sum up integer values (simple std::accumulate): " << diff.count() << " s\n";

    // Out of curiosity: parallel sum using std::reduce.
    start = high_resolution_clock::now();
    sum = std::reduce(std::execution::par, v.begin(), v.end());
	end = high_resolution_clock::now();
    diff = end - start;
    std::cout << "Ex. A. Time it took to sum up integer values (parallel std::reduce): " << diff.count() << " s\n";
}

// Part b)
int parallel_sum(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    // Recursively splits up a vector into 2 halves and sums them up in parallel.
    // If less than 1000 elements: sum up in main thread directly. No more further recursive calls.
    auto length = std::distance(begin, end);
    if (length < 1000) {
        return std::accumulate(begin, end, 0);
    }
    else {
        auto mid = begin + length / 2;
        auto ftr = std::async(std::launch::async, parallel_sum, mid, end);  // start additional thread (immediately) for recursive sum
        int sum = parallel_sum(begin, mid);  // recursive sum in current thread
        return sum + ftr.get();
    }
}

int parallel_sum_deferred(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    // Recursively splits up a vector into 2 halves and sums them up in parallel.
    // If less than 1000 elements: sum up in main thread directly. No more further recursive calls.
    auto length = std::distance(begin, end);
    if (length < 1000) {
        return std::accumulate(begin, end, 0);
    }
    else {
        auto mid = begin + length / 2;
        auto ftr = std::async(std::launch::deferred, parallel_sum, mid, end);  // start additional thread (immediately) for recursive sum
        int sum = parallel_sum(begin, mid);  // recursive sum in current thread
        return sum + ftr.get();
    }
}

void part_b() {
    std::vector<int> v(numElementsLarge, 1);
    auto start = high_resolution_clock::now();
    int sum = parallel_sum(v.begin(), v.end());
    auto end = high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Ex. B. Time it took to sum up integer values (recusively split array, tasks, immedate exec.): " << diff.count() << " s\n";
    start = high_resolution_clock::now();
    sum = parallel_sum_deferred(v.begin(), v.end());
	end = high_resolution_clock::now();
    diff = end - start;
	std::cout << "Ex. B. Time it took to sum up integer values (recusively split array, tasks, deferred): " << diff.count() << " s\n";
}


// Part d)
void part_d() {
    // Parallel sum with OpenMP (2 threads)
    std::vector<int> v(numElementsLarge, 1);
    int sumParallel = 0;
    auto start = high_resolution_clock::now();
    omp_set_num_threads(2);
    #pragma omp parallel for reduction (+:sumParallel)  // preprocessor instruction to use omp
    for (long i = 0; i < v.size(); ++i) {
        sumParallel += v[i];
    }
    auto end = high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Ex. D. Time it took to sum up integer values (open mp, 2 threads): " << diff.count() << " s\n";
}


// Part e)
// Since threads don't have return value, I sum using a global variable.
std::atomic<int> sumAtomic(0);  // global variable for thread_sum;

void thread_sum(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    // Recursively splits up a vector into 2 halves and sums them up in parallel.
    auto length = std::distance(begin, end);
    if (length < 1000) {
        sumAtomic.fetch_add(std::accumulate(begin, end, 0));
    }
    else {
        auto mid = begin + length / 2;
        std::jthread t1(thread_sum, begin, mid);
        std::jthread t2(thread_sum, mid, end);
        t1.join();
        t2.join();
    }
}


void part_e() {
    std::vector<int> v(numElementsLarge, 1);
    auto start = high_resolution_clock::now();
    thread_sum(v.begin(), v.end());
    int sum = sumAtomic.load();
    auto end = high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Ex. E. Time it took to sum up integer values (recusively split array, jthreads, atomic sum): " << diff.count() << " s\n";
}


// Part f)
void part_f() {
    // Product over a not-so-large vector.
    std::vector<long long> v(20, 2); // smaller size for product to avoid overflow
    auto start = high_resolution_clock::now();
    auto product = std::accumulate(begin(v), end(v), 1, std::multiplies<long long>()); // binary multiplies function. 1 is the initial value.
    auto end = high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Ex. F. Product: " << product << ", Time: " << diff.count() << " s\n";
}


// Part g)
void part_g() {
    std::cout << "\nEx. G: parallel vs sequential std::ranges algos\n";

    // Parallel execution of std::transform, std::sort and std::find
    std::vector<int> v(numElementsLarge);
    std::iota(v.begin(), v.end(), 0); // Fill the vector with increasing values

    // std::transform
    auto start = high_resolution_clock::now();
    std::transform(v.begin(), v.end(), v.begin(), [](int n) { return n * n; });
    auto end = high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "std::transform Time: " << diff.count() << " s\n";

    // std::sort
    start = high_resolution_clock::now();
    std::sort(v.begin(), v.end());
    end = high_resolution_clock::now();
    diff = end - start;
    std::cout << "std::sort Time: " << diff.count() << " s\n";

    // std::find
    start = high_resolution_clock::now();
    std::find(v.begin(), v.end(), 9999999);
    end = high_resolution_clock::now();
    diff = end - start;
    std::cout << "std::find Time: " << diff.count() << " s\n";

    // Now with parallel execution
    // std::transform
    start = high_resolution_clock::now();
    std::transform(std::execution::par, v.begin(), v.end(), v.begin(), [](int n) { return n * n; });
    end = high_resolution_clock::now();
    diff = end - start;
    std::cout << "Parallel std::transform Time: " << diff.count() << " s\n";

    // std::sort
    start = high_resolution_clock::now();
    std::sort(std::execution::par, v.begin(), v.end());
    end = high_resolution_clock::now();
    diff = end - start;
    std::cout << "Parallel std::sort Time: " << diff.count() << " s\n";

    // std::find
    start = high_resolution_clock::now();
    std::find(std::execution::par, v.begin(), v.end(), 9999999);
    end = high_resolution_clock::now();
    diff = end - start;
    std::cout << "Parallel std::find Time: " << diff.count() << " s\n";
}


int main() {

    part_a();
    part_b();
    part_d();
    part_e();
    part_f();
    part_g();

	return 0;
};