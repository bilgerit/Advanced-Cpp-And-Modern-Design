// StopWatch class.
// Can be used to measure runtimes of arbitrary operations.
#pragma once
#include <chrono>

class StopWatch {
    // Traditional stop watch.
    // Keeps trach of the start and stop time. Both can be reset. 
    // Difference between the two (elapsed time) can be be retrieved.
private:
    std::chrono::high_resolution_clock::time_point start_time_point;
    std::chrono::high_resolution_clock::time_point end_time_point;
    bool is_running{ false };
    StopWatch(const StopWatch&) = delete;
    StopWatch& operator=(const StopWatch&) = delete;

public:
    StopWatch() = default;

    void StartStopWatch();
    void StopStopWatch();
    void Reset();

    double GetTime() const;
};
