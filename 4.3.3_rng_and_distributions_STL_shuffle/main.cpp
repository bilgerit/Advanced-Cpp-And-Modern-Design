// Shuffling of vectors using RNGs.
// Tobias Bilgeri, 06.01.2024
#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>


using namespace std;
using i32 = int32_t;

template <typename Container>
void print_container(const Container& c) {
    for (const auto& el : c) {
        std::cout << el << " ";
    }
    std::cout << "\n\n\n";
}

struct MyRand {
    // simple wrapper around std::rand
    int operator() (i32 n) const {
        return rand() / RAND_MAX * (n + 1);
    }
};

int main() {

    const i32 num_elements = 100;
    auto v = vector<i32>(100);
    iota(v.begin(), v.end(), 1);
    print_container(v);

    // (random_shuffle is deprecated since C++17)

    // random_shuffle(v.begin(), v.end(), MyRand());
    // random_shuffle(v.begin(), v.end(), mt19937{ random_device{}() });
    // random_shuffle(v.begin(), v.end(), default_random_engine{ random_device{}() });
    // random_shuffle(v.begin(), v.end(), linear_congruential_engine<uint_fast32_t, 48271, 0, 2147483647>{std::random_device{}()});

    // shuffle with different generators
    shuffle(v.begin(), v.end(), mt19937{ random_device{}() });
    print_container(v);
    shuffle(v.begin(), v.end(), default_random_engine{ random_device{}() });
    print_container(v);
    shuffle(v.begin(), v.end(), linear_congruential_engine<uint_fast32_t, 48271, 0, 2147483647>{std::random_device{}()});
    print_container(v);

	return 0;
}