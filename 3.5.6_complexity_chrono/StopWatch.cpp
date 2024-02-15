#pragma once
#include "StopWatch.h"

void StopWatch::StartStopWatch() {
    // Set start time to now.
    start_time_point = std::chrono::high_resolution_clock::now();
    is_running = true;
}

void StopWatch::StopStopWatch() {
    // Set end time to now (unless the watch was stopped earlier and not restarted since).
    if (!is_running) return;
    end_time_point = std::chrono::high_resolution_clock::now();
    is_running = false;
}

void StopWatch::Reset() {
    // Set the start and end time to now. 
    start_time_point = std::chrono::high_resolution_clock::now();
    end_time_point = start_time_point;
}

double StopWatch::GetTime() const {
    // Returns time between when the stop watch was started and stopped.
    std::chrono::duration<double> elapsed = end_time_point - start_time_point;
    return elapsed.count();
}