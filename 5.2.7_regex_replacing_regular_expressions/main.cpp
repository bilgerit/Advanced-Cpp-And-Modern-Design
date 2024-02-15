// regex_replace
// Replace characters or patterns by alternative characters or patterns.
// Tobias Bilgeri, 27.01.2024
#pragma once
#include <iostream>
#include <string>
#include <regex>

using String = std::string;
using Regex = std::regex;

int main() {
    String original_text("Quick brown fox");
    String replacement_character("*");
    Regex characters_to_replace("a|e|i|o|u");

    String new_text = std::regex_replace(
        original_text,
        characters_to_replace,
        replacement_character);

    std::cout << original_text << std::endl;
    std::cout << new_text << std::endl;

    return 0;
}