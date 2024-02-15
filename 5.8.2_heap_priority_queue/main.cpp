// Priority Queue
// 
// We create some priority queues with different comparators:
//    default, std::greater, lambda fn
// 
// Note that we covered Priority Queues in earlier levels, including 
// concurrent prio queues. 
// 
// Tobias Bilgeri, 28.1.2024
#include <iostream>
#include <queue>
#include <vector>

template<typename T> using Vector = std::vector<T>;

int main() {

    {
        // a. create a priority_queue and print elements by popping them.
        std::priority_queue<int> pq;
        Vector<int> elements{ 10,5,20,30,25,7,40 };

        for (const int element : elements) {
            pq.push(element);
        }

        std::cout << "Priority queue: ";

        while (!pq.empty()) {
            std::cout << pq.top() << " ";
            pq.pop();
        }

        std::cout << "\n";
    }

    {
        // b. same as a but use an alternative comparison operation std::greater.
        std::priority_queue<int, Vector<int>, std::greater<int>> pq;
        Vector<int> elements{ 10,5,20,30,25,7,40 };

        for (const int element : elements) {
            pq.push(element);
        }
        std::cout << "Pq w/ std::greater comparator: ";

        while (!pq.empty()) {
            std::cout << pq.top() << " ";
            pq.pop();
        }

        std::cout << "\n";
    }

    {
        // c. use custom comparison operation
        auto cmp = [](int left, int right) { 
            return (left > right); };

        std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);
        Vector<int> elements{ 10,5,20,30,25,7,40 };

        for (int element : elements) {
            pq.push(element);
        }

        std::cout << "Pq w/ lambda comparator: ";

        while (!pq.empty()) {
            std::cout << pq.top() << " ";
            pq.pop();
        }

        std::cout << "\n";
    }

    return 0;
}
