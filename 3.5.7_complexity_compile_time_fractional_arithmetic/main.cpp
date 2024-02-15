// In this exercise, we take a look at rational numbers in C++ using std::ratio.
// 
// Notes: Ratio is a struct with 2 member variables: num (numerator) and den (denominator).
//        Making use of the fact that they are rational numbers then requires using 
//        extra functionality such as std::ratio_add, etc.
//        Basic arithmetic manipulations (exercise b) preserve the numbers as rational.
//       
// Tobias Bilgeri, 15. Dec. 2023
#pragma once
#include <iostream>
#include <ratio>


int main() {
    // a) Create a number of instances of std::ratio and print them.
    std::cout << "Exercise a)\n\n";
    std::ratio<1, 2> r1;
    std::ratio<2, 4> r2;
    std::ratio<4, 9> r3;

    std::cout << "r1: " << r1.num << "/" << r1.den << "\n";
    std::cout << "r2: " << r2.num << "/" << r2.den << "\n";
    std::cout << "r3: " << r3.num << "/" << r3.den << "\n";


    // b) Create two std::ratio instances; add, subtract, multiply and divide them.
    std::cout << "\n\nExercise b)\n\n";
    using result_add = std::ratio_add<decltype(r1), decltype(r2)>::type;
    using result_subtract = std::ratio_subtract<decltype(r1), decltype(r2)>::type;
    using result_multiply = std::ratio_multiply<decltype(r1), decltype(r2)>::type;
    using result_divide = std::ratio_divide<decltype(r1), decltype(r2)>::type;

    std::cout << "r1 + r2: " << result_add::num << "/" << result_add::den << "\n";
    std::cout << "r1 - r2: " << result_subtract::num << "/" << result_subtract::den << "\n";
    std::cout << "r1 * r2: " << result_multiply::num << "/" << result_multiply::den << "\n";
    std::cout << "r1 / r2: " << result_divide::num << "/" << result_divide::den << "\n";

    return 0;
};