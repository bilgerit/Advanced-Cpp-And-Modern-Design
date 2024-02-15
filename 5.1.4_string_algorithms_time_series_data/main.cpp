// Load some time series data from a CSV.
// Approach:
//   - load file via ifstream
//   - each line is written to a string
//   - each line string is then split on commas and all parts are written to a vector
//   - the first entry is converted to a boost date, all others are converted to doubles.
//   - the result is stored as a tuple (date, numeric_values).
//   - all touples are collected to a list.
// Tobias Bilgeri, 05.01.2024
#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <tuple>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

using Date = boost::gregorian::date;
using Data = std::tuple<Date, std::vector<double>>;
using ResultSet = std::list<Data>;

ResultSet loadCustomCSV(const std::string& filename) {
    // Load data from a CSV of the following format:
    // {Date,Open,High,Low,Close,Volume,Adj Close}
    // With date being a string of format YYYY-MM-DD

    std::cout << "About to load file: " << filename << "\n";

    ResultSet result;

    // Input File Stream
    std::ifstream file(filename);

    // String to store the individual lines
    std::string line;
    
    // Array to store the individual parts of the string.
    std::vector<std::string> elements;
    std::vector<double> numeric_elements;

    // Skip header
    std::getline(file, line);  

    while (std::getline(file, line)) {

        elements.clear();
        numeric_elements.clear();

        boost::split(
            elements,
            line, 
            boost::is_any_of(","));

        Date date = boost::gregorian::from_string(elements[0]);

        for (size_t i = 1; i < elements.size(); ++i) {
            numeric_elements.push_back(
                boost::lexical_cast<double>(elements[i]));
        }

        result.emplace_back(Data(date, numeric_elements));
    }

    std::cout << "Finished loading the file.\n";

    return result;
}

int main() {
    ResultSet data = loadCustomCSV("test_data.csv");

    std::cout << "Date\tOpen\tHigh\tLow\tClose\tVolume\tAdj Close\n";
    for (const Data& row : data) {

        std::cout << boost::gregorian::to_iso_string(std::get<0>(row)) << ": ";
        
        for (double values : std::get<1>(row)) {
            std::cout << values << '\t';
        }
        std::cout << '\n';
    }

    return 0;
}