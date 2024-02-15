// Heap 101
// 
// We use std::ranges::make_heap.
// This allows us to take an underlying container (vector in this case)
// and turn it into a heap, with all the associated heap functionalities
// defined in <algorithms>.
// 
// Tobias Bilgeri, 28.1.2024
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void printl(const auto& s) {
    std::cout << s << "\n";
}

void print_container(const auto& c) {
    for (const auto& el : c) {
        std::cout << el << " ";
    }
    std::cout << "\n";
}

int main() {
    // create vector
    std::vector<int> v{ 1, 2, 3, 4, 9, 8, 7, 6, 5, };
    printl("Vector: ");
    print_container(v);

    // call make_heap
    std::ranges::make_heap(v);
    printl("Vector after calling make_heap: ");
    print_container(v);

    /*
    structure of the heap binary tree:

            9
          /   \
         6     8
        / \   / \
       5   2 3   7
      / \
     4   1

    */

    // pop_head: pops root
    std::ranges::pop_heap(v); // swap first element to last-1
    printl("Vector after calling pop_heap: ");
    print_container(v);
    v.pop_back(); // removes the last element (reduces size of v)
    printl("Vector after calling v.pop_back: ");
    print_container(v);

    // call push_heap
    v.push_back(99); // adds the element to the container underlying container.
    printl("Vector after calling v.push_back: ");
    print_container(v);
    std::ranges::push_heap(v); // expands the heap to include 99
    printl("Vector after calling push_heap: ");
    print_container(v);

    // sort the heap
    std::ranges::sort_heap(v);
    printl("Vector after calling sort_heap: ");
    print_container(v);

    // find largest element
    printl("Largest element: ");
    printl(v.back());
    
    return 0;
}