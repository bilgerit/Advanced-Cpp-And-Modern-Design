// We take a string-encoded map, extract the data, and store it as a map.
// Tobias Bilgeri, 26.01.2024
#pragma once
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>

using Regex = std::regex;
using String = std::string;
template<typename T> using Vector = std::vector<T>;
template<typename K, typename V> using Map = std::map<K, V>;

int main() {
    String sA("a = 1, b = 2, c = 3");

    // a. extract string "a = 1", "b = 2", etc..
    {
        std::cout << "EXERCISE A\n";

        Regex seperator(", ");

        // find strings ahead/after/in-between seperators:
        std::sregex_token_iterator iter(sA.begin(), sA.end(), seperator, -1);

        std::sregex_token_iterator end;

        Vector<String> extractedPairs;
        while (iter != end) {
            extractedPairs.push_back(*iter);
            ++iter;
        }

        // print results
        for (const String& pair : extractedPairs) {
            std::cout << pair << std::endl;
        }
    }

    // b. store map-like string as map using boost.
    {
        std::cout << "\nEXERCISE B\n";
        
        // boost::split_regex splits a string and writes individual chunks to a vector.
        //   (so that we don't have to do it ourselves via an iterator as above)
        Vector<String> extractedPairs;
        boost::algorithm::split_regex(
            extractedPairs, 
            sA, 
            boost::regex(", "));

        // format the individual chunks ("a = 1" or similar) as "str key: int val" pairs.
        Map<String, int> keyValuePairs;
        for (const String& pair : extractedPairs) {
            Vector<String> keyValue;
            boost::algorithm::split_regex(
                keyValue, 
                pair, 
                boost::regex(" = "));

            keyValuePairs[keyValue[0]] = std::stoi(keyValue[1]);
        }

        // print
        for (const auto& pair : keyValuePairs) {
            std::cout << pair.first << " = " << pair.second << std::endl;
        }
    }

    return 0;
}