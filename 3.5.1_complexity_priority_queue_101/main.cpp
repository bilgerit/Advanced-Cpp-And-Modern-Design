// In this exercise, we look at priority queues.
// Unlike regular queues, which act on a FIFO basis, we can implement a custom
// comparator (or use defaults) to continuosly keep the container sorted according to
// whatever rule the comparator implements.
// Other than that, the priority queue has typical queue utility: pop(), push(), etc.
// Tobias Bilgeri, 3. Dec. 2023
#pragma once
#include <iostream>
#include <queue>


template < class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type> >
void priority_queue_operations(std::priority_queue<T, Container, Compare>& pq) {
	// Simple utility function to avoid copying code across exercise a, b, and c.
	// Sequentially adds and removes elements from a priority queue, while printing
	// information to the console.
	std::cout << "Adding to queue: 66, 22, 44\n";
	pq.push(66);
	pq.push(22LL);
	pq.push(44LL);

	std::cout << "Top element: " << pq.top() << "\n";
	pq.pop();
	std::cout << "Top element after calling .pop(): " << pq.top() << "\n";

	std::cout << "Adding to queue: 11, 22, 33\n";
	pq.push(11LL);
	pq.push(22LL);
	pq.push(33LL);

	std::cout << "Popping the top element: " << pq.top() << std::endl;
	pq.pop();

	while (!pq.empty()) {
		std::cout << "Popping the top element: " << pq.top() << std::endl;
		pq.pop();
	}
}


int main() {

	{
		// Exercise a)
		// Main idea: Push some integral type objects into a priority queue.
		//            Then pop them.
		//            Observation: The order in which they get popped is independent
		//                         of the entry (push) order. Instead, larger values
		//                         get popped first.
		std::cout << "Exercise A: Default priority queue.\n\n";
		std::priority_queue<long long> pq;

		priority_queue_operations(pq);
	}

	{
		// Exercise b)
		// Main idea: Priority queue can also accept template arguments defining
		//            how it gets sorted (comparator) and container type.
		// Container type herein is a simple double-ended queue (makes sense since we
		// often perform operations on the last element).
		// Comparator is now std::greater<T>, which means that the smallest elements
		// get moved to the top and hence get popped with highest priority.
		std::cout << "\n\nExercise B: Priority queue with smallest elements at the top.\n\n";
		using T = long long;
		std::priority_queue<T, std::deque<T>, std::greater<T>> pq;

		priority_queue_operations(pq);
	}

	{
		// Exercise c)
		// Main idea: same as exercise b except that we pass a custom comparator via
		// a lambda function.
		std::cout << "\n\nExercise C: Custom comparator via a lambda.\n\n";
		using T = long long;
		auto is_greater = [](const T& a, const T& b) { return a > b; };
		std::priority_queue<T, std::deque<T>, decltype(is_greater)> pq(is_greater);

		priority_queue_operations(pq);
	}

	return 0;
};