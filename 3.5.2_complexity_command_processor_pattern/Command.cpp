#pragma once
#include "Command.h"

Command::Command(const FunctionType& algorithm, long priority) : algo(algorithm), ID(priority) {};

void Command::Execute(double x) {
	// Introduce delay to simulate a heavy algorithm 
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	std::cout << algo(x) << '\n';
}

int Command::priority() const { return ID; };