// Command-Processor Pattern.
//  ... subtype of producer-consumer pattern.
// First, we create a bunch of Command objects (= isolated workloads to be carried out), each with a specific priority.
// Second, we execute them sequentially in a while-loop.
// Tobias Bilgeri, 13. Dec. 2023
#pragma once
#include "Command.h"
#include <queue>

int main() {

	// Compare Command type priorities.
	auto compareCommandPriority = [](const Command& c1, const Command& c2) { return c1.priority() < c2.priority(); };


	// -------------
	// PRODUCER CODE
	// -------------
	
	// Create a few Command objects.
	auto algo1 = [](const double& d) { return d + 1; };
	auto algo2 = [](const double& d) { return d + 2; };
	auto algo3 = [](const double& d) { return d + 3; };
	auto algo4 = [](const double& d) { return d + 4; };
	auto algo5 = [](const double& d) { return d + 5; };

	Command c1(algo1, 1L);
	Command c2(algo2, 2L); // tie
	Command c3(algo3, 2L); // tie
	Command c4(algo4, 2L); // tie
	Command c5(algo5, 3L);

	// Create priority queue.
	// Note: Execution order on my system: c5 - c3 - c4 - c2 - c1.
	std::priority_queue<Command, std::deque<Command>, decltype(compareCommandPriority)> pq(compareCommandPriority);
	pq.push(c1);
	pq.push(c2);
	pq.push(c3);
	pq.push(c4);
	pq.push(c5);


	// -------------
	// PRODUCER CODE
	// -------------

	// Execute each command in the priority queue.

	while (!pq.empty()) {
		std::cout << "ID of command at the top of the priority queue: " << pq.top().priority() << "; About to execute and pop it.\n";

		// Note: can't use pq.top().Execute() since top() is a const fct and Execute is non-const. Hence, top() has no guarantee that
		//       Execute() wouldn't alter the state of the pq.
		//       Therefore, we need to pop the element, and then call Execute.
		Command topElement = pq.top();
		topElement.Execute(0);
		pq.pop();
	}

	return 0;
};