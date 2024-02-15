// We again use std::regex_search.
// However, we additionally use std::smatch.
// This allows us to go beyond returning a simple bool and instead allows us finding all
// occurences of a given regex.
// Tobias Bilgeri, 26.01.2024
#pragma once
#include <regex>
#include <string>
#include <iostream>

int main() {
    // regex pattern to search for
    std::regex mySearchReg("(rain)|(Spain)");

    // string in which we search
    std::string myText("The rain in Spain stays mainly on the plain");

    // smatch: stores the matched string of a std::regex_search.
    std::smatch match;

    while (std::regex_search(myText, match, mySearchReg)) {

        std::cout << "Found match: " << match[0] << '\n';
        std::cout << "Remaining string: " << match.suffix().str() << "\n";

        // search in rest of string
        myText = match.suffix().str();
    }

    return 0;
}