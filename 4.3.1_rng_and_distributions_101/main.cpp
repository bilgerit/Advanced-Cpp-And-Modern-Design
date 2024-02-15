// Random number generation 101
// Tobias Bilgeri, 05.01.2024
#pragma once
#include <iostream>
#include <random>
#include <vector>

template <typename T>
void println(const T& printable) {
    std::cout << printable << "\n";
}

template <typename Engine, typename Distribution>
std::vector<typename Distribution::result_type> generate_rand_nums(Engine& eng, Distribution& distrib, size_t n) {
    // Generic RNG generator
    std::vector<typename Distribution::result_type> ans;
    for (int i = 0; i != n; i++) {
        ans.push_back(distrib(eng));
    }
    return ans;
}

int main() {

	// ex. a. try different engines: linear congruential, mte, mte64
	{
        println("Exercise a");
        // RNG Engines
        std::linear_congruential_engine<std::uint32_t, 48271, 0, 2147483647> lce;
        std::mt19937 mte;
        std::mt19937_64 mte64;

        // Distributions
        std::uniform_int_distribution<int> distrib(1, 100);

        // Generate the Numbers
        println("linear congruential engine:");
        for (int i = 0; i < 10; ++i) {
            std::cout << distrib(lce) << " ";
        }
        std::cout << "\n";

        println("mersenne twister engine (32-bit): ");
        for (int i = 0; i < 10; ++i) {
            std::cout << distrib(mte) << " ";
        }
        std::cout << "\n";

        println("mersenne twister engine (64-bit): ");
        for (int i = 0; i < 10; ++i) {
            std::cout << distrib(mte64) << " ";
        }
        std::cout << "\n";
	}

    // ex. b. try different distributions
    {
        println("\n\nExercise b");

        std::mt19937 mte;

        std::normal_distribution<> normal;
        std::chi_squared_distribution<> chi_squared(1.0);
        std::bernoulli_distribution bernoulli(0.5);
        std::cauchy_distribution<> cauchy;

        std::cout << "mormal distr: ";
        for (int i = 0; i < 10; ++i) {
            std::cout << normal(mte) << ", ";
        }
        std::cout << "\n";

        std::cout << "chi-squared distr: ";
        for (int i = 0; i < 10; ++i) {
            std::cout << chi_squared(mte) << ", ";
        }
        std::cout << "\n";

        std::cout << "bernoulli distr: ";
        for (int i = 0; i < 10; ++i) {
            std::cout << bernoulli(mte) << ", ";
        }
        std::cout << "\n";

        std::cout << "cauchy distr: ";
        for (int i = 0; i < 10; ++i) {
            std::cout << cauchy(mte) << ", ";
        }
        std::cout << "\n";
    }

    // ex. c. 
    {
        println("\nExercise c");

        std::mt19937 mte;
        std::normal_distribution<> normal;
        auto res = generate_rand_nums(mte, normal, 10);
        for (const auto& el : res) {
            std::cout << el << " ";
        }
    }

	return 0;
}