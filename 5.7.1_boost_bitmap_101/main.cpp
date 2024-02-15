// Bimap 101
// 
// boost::bimap behaves similar to maps in the standard library.
// It differs for example in the fact that we can iterate through 'left' and 
// 'right' side (similar to 'keys' and 'values'), which we demonstrate here.
// 
// Tobias Bilgeri, 28.1.2024
#pragma once
#include <iostream>
#include <boost/bimap.hpp>

int main() {
    using BmPeople = boost::bimap<std::string, int>;
    using BmPeopleType = BmPeople::value_type;

    BmPeople people;

    // a. populate bimap (note: cant use .emplace())
    people.insert(BmPeopleType("Bob", 30));
    people.insert(BmPeopleType("Alice", 25));

    // b. print the left and right map
    //
    // Note: the bimap can also use range based for loops, e.g.:
    //       for (const auto& [k, v] : people) { std::cout << k << " maps to " << v << "\n"; }

    std::cout << "left map:\n";
    for (auto it = people.left.begin(); it != people.left.end(); ++it) {
        std::cout << it->first << " maps to " << it->second << "\n";
    }

    std::cout << "\nright map:\n";
    for (auto it = people.right.begin(); it != people.right.end(); ++it) {
        std::cout << it->first << " maps to " << it->second << "\n";
    }

    // c. search age based on name, and vice versa.
    std::cout << "\nage of Bob: " << people.left.at("Bob") << "\n";
    std::cout << "30 year old person is: " << people.right.at(30) << "\n";

    // d. iterate using 'third view' / 'relations'
    std::cout << "\nrelations / third view:\n";
    for (auto it = people.begin(); it != people.end(); ++it) {
        std::cout << (*it).get_left() << " maps to " << it->right << "\n";
    }

    return 0;
}