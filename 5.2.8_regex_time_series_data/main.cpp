// Time Series Data from CSV file
// Same as exercise 5.1.4, but rather than splitting the line-string on commas, we directly use 
// a regex-statement, and then read out the content of the smatch object.
// Tobias Bilgeri, 27.01.2024
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include <tuple>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lexical_cast.hpp>

using String = std::string;
using Regex = std::regex;
using Ifstream = std::ifstream;
using Smatch = std::smatch;
using Date = boost::gregorian::date;
template<typename T> using Vector = std::vector<T>;

using Data = std::tuple<Date, Vector<double>>;
using ResultSet = std::list<Data>;

int main() {
    Ifstream file("test_data.csv");

    Regex rowReg(
        "([0-9]{4}-[0-9]{2}-[0-9]{2}),"                               // Date string
        "([0-9.]+),([0-9.]+),([0-9.]+),([0-9.]+),([0-9]+),([0-9.]+)"  // Numeric Columns: Open, High, Low, Close, Volume, Adj Close
    );

    String line;
    Smatch match;
    ResultSet resultSet;

    if (file.is_open()) {

        // skip header
        std::getline(file, line);

        while (std::getline(file, line)) {

            if (std::regex_search(line, match, rowReg) && match.size() > 7) {

                Date date(boost::gregorian::from_string(match[1]));

                Vector<double> values;
                for (int i = 2; i <= 7; ++i) {
                    values.push_back(boost::lexical_cast<double>(match[i]));}

                resultSet.emplace_back(std::make_tuple(date, values));}}

        file.close();}

    // print
    std::cout << "Date, \t\tOpen, \tHigh, \tLow, \tClose, \tVolume, \tAdj Close\n";

    for (const auto& data : resultSet) {
        std::cout << std::get<0>(data) << ":\t";

        for (const auto& value : std::get<1>(data)) {
            std::cout << value << " \t";}

        std::cout << "\n";}

    return 0;
}