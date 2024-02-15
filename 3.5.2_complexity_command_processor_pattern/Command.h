// Simple command class for demonstration purpose.
// Tobias Bilgeri, 13. Dec. 2023
#pragma once
#include <functional>
#include <thread>
#include <chrono>
#include <iostream>

using FunctionType = std::function<double(double)>;

class Command {
	// Simple Command class.
	// Contains an Execute method to simulate a workload, and a priority method to identify it's priority in a priority queue.
	// Priority is stored as an integral type named ID.
	// A function object algo is called when running the Execute method. 

private: 
	FunctionType algo;
	long ID;   // priority of command 
public: 
	Command(const FunctionType& algorithm, long priority);
	void Execute(double x);
	int priority() const;
};
