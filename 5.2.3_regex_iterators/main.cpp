// Like in the previous exercise where we used std::smatch,
// we again find all matching occurences in a sequence.
// However, this time we make use of the regex iterator (std::sregex_iterator).
// Tobias Bilgeri, 26.01.2024
#pragma once
#include <regex>
#include <string>
#include <set>
#include <iostream>

using String = std::string;
using Regex = std::regex;
using SRegexIterator = std::sregex_iterator;
template<typename T> using Set = std::set<T>;


int main() {
    String S2 = "1,1,2,3,5,8,13,21";

    // Regex:
    // \\d        : match digit
    // +          : match one or more [digits]
    // ,          : match comma.
    // ?          : match zero or one [commas]
    // "(\\d+),?  : match some digits optionally followed by a single comma.
    Regex myReg("(\\d+),?");

    // a.
    // find matches.
    SRegexIterator it(S2.begin(), S2.end(), myReg);
    SRegexIterator end;

    // b, c.
    std::cout << "EXERCISE A, B, C\n";

    Set<String> result;

    // add matches to set.
    for (; it != end; ++it) {
        result.insert(it->str());
    }

    // print set elements.
    for (const String& s : result) {
        std::cout << s << '\n';
    }

    // d.
    // same as b + c but store integers instead.
    // 
    // note that sets are sorted: 
    // when storing strings (prev exercise), "21" comes ahead of "3".
    // now, 21 obvously comes after 3. 
    std::cout << "\n\nEXERCISE D\n";

    std::set<int> resultInt;

    it = SRegexIterator(S2.begin(), S2.end(), myReg);

    for (; it != end; ++it) {
        resultInt.insert(
            // map strings to integers
            std::stoi(it->str()
            )
        );
    }

    for (const int& i : resultInt) {
        std::cout << i << '\n';
    }

    return 0;
}