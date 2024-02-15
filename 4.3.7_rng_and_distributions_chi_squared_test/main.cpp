// Chi-squared test.
// Like exercise 4.3.2. but w/ Chi-Squared according to the forum: https://quantnet.com/threads/7-clarification-of-requirement.33844/
// Tobias Bilgeri, 05.01.2024
#pragma once
#include <iostream>
#include <map>
#include <random>
#include <string>

// code from exercise 4.3.2
template <typename T>
void println(const T& printable) {
    std::cout << printable << "\n";
}

// code from exercise 4.3.2
template <typename Dist, typename Eng>
void GenerateRandomNumbers(Eng eng, Dist d, int32_t num_trials, const std::string& s) {
    // Take engine + distribution + num_trials + name, and generate a set of random
    // numbers stored in a map.
    // Then print the frequencies to termina.
    std::map<int64_t, int32_t> counts;

    for (int32_t i = 0; i != num_trials; i++) {
        auto rand_var = static_cast<int64_t>(d(eng));
        counts[rand_var] += 1;
    }

    println("Generated random numbers w/ Distribution " + s + " -- Frequencies:");
    for (const auto& [value, count] : counts) {
        println(std::to_string(value) + ": " + std::to_string(count));
    }
}



int main()
{
    // initialize variables for random number generation: 
    const int num_trials = 10'000;
    const int seed = 42;
    std::mt19937_64 engine(seed);

    // generate chi-square distributed random variables with differing degrees of freedom
    for (int degrees_of_freedom : { 1, 3, 6, 9 }) {

        std::chi_squared_distribution<double> distribution(degrees_of_freedom);

        std::string printing_label = "Chi-Squared w/ degrees of freedom = " + std::to_string(degrees_of_freedom);

        GenerateRandomNumbers(engine, distribution, num_trials, printing_label);
    }

    return 0;
}