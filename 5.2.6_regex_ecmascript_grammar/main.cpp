// In this exercise, we parse numbers from a string that follow the ECMAScript grammar.
// Tobias Bilgeri, 26.01.2024
#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include <string>

int main() {
    std::regex ecmaReg(
        "((\\+|-)?[[:digit:]]+)"             // plus or minus optionally followed by some digits
        "(\\.(([[:digit:]]+)?))"             // optional have some decimal point and digits behind it
        "?((e|E)((\\+|-)?)[[:digit:]]+)?");  // optionally have some exponent notation "eXXX"

    std::vector<std::string> testNumbers = {
        "1", "-1", "+1", "1.2", "-1.2", "+1.2", "1e2", "-1e2", "+1e2", "1.2e3", "-1.2e3", "+1.2e3", "a", "1a", "1.2a", "1ea", "1.1ea"};

    for (const auto& num : testNumbers) {
        if (std::regex_match(num, ecmaReg)) {
            std::cout << num << " is a valid number. Converted to double: " << std::stod(num) << "\n";
        }
        else {
            std::cout << num << " is not a valid number.\n";
        }
    }

    return 0;
}