// In this exercise, we implement and test a simple stop watch.
// Tobias Bilgeri, 15. Dec. 2023
#pragma once
#include <thread>
#include <iostream>
#include "StopWatch.h"


int main() {
    // Create & start stopwatch.
    StopWatch sw;
    sw.StartStopWatch();

    // Simulate some work (workload duration = 2 seconds).
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Stop stop watch and print elapsed time.
    sw.StopStopWatch();
    std::cout << "Elapsed time: " << sw.GetTime() << " seconds\n";

    return 0;
}