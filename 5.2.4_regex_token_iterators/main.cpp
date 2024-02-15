// std::sregex_token_iterator
// The sregex_token_iterator allows to find all elements equal to, or before/in-between-after,
// a specific seperator within a string.
// Tobias Bilgeri, 05.01.2024
#pragma once
#include <regex>
#include <string>
#include <vector>
#include <iostream>


enum RegexIteratorMode {
    // C-Style enumeration to make the behaviour of std::sregex_token_iterator a bit more 
    // transparent. 
    MatchedExpressions = 0,
    SubsequencesBetweenMatches = -1
};


int main() {
    // Define the regular expression and the target string
    std::regex myReg10("/"); // match on "/".
    std::string S3 = "2016/3/15";

    // a. Extract the data 2016, 3 and 15 from the string
    {
        // Create a regex token iterator. The last argument is -1, which means
        // we want to find all subsequences between (and before/after) matched 
        // regular expressions.
        std::sregex_token_iterator iter(
            S3.begin(), 
            S3.end(), 
            myReg10, 
            RegexIteratorMode::SubsequencesBetweenMatches);

        std::sregex_token_iterator end;

        // Store the extracted data in a vector
        // (Note: since we always expect 3 elements, we could also use a tuple or array).
        std::vector<std::string> extractedData;

        while (iter != end) {
            extractedData.push_back(*iter);
            ++iter;
        }

        // Print the extracted data (= Year, Month, Day)
        std::cout << "Extracted data: ";
        for (const auto& data : extractedData) {
            std::cout << data << " ";
        }
        std::cout << std::endl;
    }

    // b. Extract the '/' character from the string
    {
        // Create a regex token iterator. The last argument is 0, which means
        // we want to find all the matched regular expressions.
        std::sregex_token_iterator iter(
            S3.begin(), 
            S3.end(), 
            myReg10, 
            RegexIteratorMode::MatchedExpressions);
        
        std::sregex_token_iterator end;

        // Store the extracted separators in a vector
        std::vector<std::string> extractedSeparators;
        while (iter != end) {
            extractedSeparators.push_back(*iter);
            ++iter;
        }

        // Print the extracted separators
        std::cout << "Extracted separators: ";
        for (const auto& separator : extractedSeparators) {
            std::cout << separator << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}