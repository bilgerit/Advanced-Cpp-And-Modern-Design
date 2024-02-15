// Template Method Pattern for Processor
//
// Processor herein is contained of 3 logic blocks: Factory -> Compute -> Dispatch
//
// All three logic blocks are defined via "templates" (=std::function types) and
// hence modifiable at runtime.
//
// The individual blocks are quite flexible thanks to only needing to satisfy
// the function template. This allows us to for example implement parallel
// algorithms within a block.
// In this example, I compute a sum and product on a large array within the Compute
// method, which I do both sequentially as well as in parallel (using lazy execution
// in this example).
//
// Tobias Bilgeri, 14.02.2024
#include <iostream>
#include <array>
#include <numeric>
#include <chrono>

#include "TmpProcessor.h"

struct StopWatch
{
    // simple stopwatch implementation
    // used to measure time between when Start() and End() members are called.
    std::chrono::high_resolution_clock::time_point start_, end_;
    long long duration_us_;

    void Start()
	{
        start_ = std::chrono::high_resolution_clock::now();
    }

    void End()
	{
        end_ = std::chrono::high_resolution_clock::now();
        duration_us_ = std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_).count();
        this->PrintDuration();
	}

    void PrintDuration() const
	{
        std::cout << "Duration: " << duration_us_ << "us\n.";
	}
};


int main() {
    StopWatch sw;
    constexpr int NUM_ELEMENTS = 200'000;

    // ex a. Example: Sequential Processor.
    {
        auto factory = []() -> int { return 1; };

        auto compute = [&NUM_ELEMENTS](const int& inp) -> int
            {
				// compute prod + sum on a large array.
                std::array<int, NUM_ELEMENTS> arr;
                arr.fill(inp);
                int sum = std::accumulate(arr.begin(), arr.end(), 0);
                int prod = std::reduce(arr.begin(), arr.end(), 1, std::multiplies<int>());
                return sum + prod;
			};

        auto dispatch = [](const int& inp) -> void { std::cout << "Ex. a. Example result (sequential): " << inp << "\n"; };

        sw.Start();

        TmpProcessor<int> processor(factory, compute, dispatch);
        processor.algorithm();

        sw.End();
    }


    // ex. b. Example: Parallel Processor
    {
        auto factory = []() -> int { return 1; };

        auto compute = [&NUM_ELEMENTS](const int& inp) -> int
            {
                // compute prod + sum on a large array. The two operations are done in parallel. 
			    // Note: An easy way to parallelize this is using default parallel execution for std::algorithms / std::numerics algorithms.
                std::array<int, NUM_ELEMENTS> arr;
                arr.fill(inp);
                std::future<int> sum = std::async(std::launch::deferred, [&arr]() {return std::accumulate(arr.begin(), arr.end(), 0); });
                std::future<int> prod = std::async(std::launch::deferred, [&arr]() {return std::reduce(arr.begin(), arr.end(), 1, std::multiplies<int>()); });
        		int ans = sum.get() + prod.get();
                return ans;
            };

        auto dispatch = [](const int& inp) -> void { std::cout << "Ex. b. Example result (parallel): " << inp << "\n"; };

        sw.Start();

    	TmpProcessor<int> processor(factory, compute, dispatch);
        processor.algorithm();

        sw.End();
    }

    return 0;
}