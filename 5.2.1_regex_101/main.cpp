// In this exercise, we look at some regex patterns.
// Examples include matching lower case characters, specific and variable
// numbers of digits, words, etc.
// Tobias Bilgeri, 26.01.2024
#pragma once
#include <iostream>
#include <regex>
#include <string>
#include <tuple>

using Regex = std::regex;
using String = std::string;
template<typename ...Types> using Tuple = std::tuple<Types...>;

void printb(const bool b) {
    std::cout << std::boolalpha << b << "\n"; };

int main() {

    // ex. a.
    std::cout << "EXERCISE A \n";

    Regex myReg("[a-z]*");  // match 0 or more lower case letters.
    Regex myReg2("[a-z]+"); // match 1 or more lower case letters.
    Tuple t = { "axa", "1", "b", "ZZ TOP", "" };

    printb(std::regex_match(std::get<0>(t), myReg)); // t
    printb(std::regex_match(std::get<1>(t), myReg)); // f
    printb(std::regex_match(std::get<2>(t), myReg)); // t
    printb(std::regex_match(std::get<3>(t), myReg)); // f
    printb(std::regex_match(std::get<4>(t), myReg)); // true

    printb(std::regex_match(std::get<0>(t), myReg2)); // t
    printb(std::regex_match(std::get<1>(t), myReg2)); // f
    printb(std::regex_match(std::get<2>(t), myReg2)); // t
    printb(std::regex_match(std::get<3>(t), myReg2)); // f
    printb(std::regex_match(std::get<4>(t), myReg2)); // false

    // ex. b.
    std::cout << "\nEXERCISE B \n";

    Regex myNumericReg("\\d{2}"); // match 2 digits

    printb(std::regex_match("34", myNumericReg)); // t
    printb(std::regex_match("34", myNumericReg)); // t
    printb(std::regex_match("3", myNumericReg)); // false
    printb(std::regex_match("345", myNumericReg)); // false

    // ex. c.
    std::cout << "\nEXERCISE C \n";

    // match new or delete (brackets are omitted and only used to define the
    // OR logic)
    Regex myAltReg("(new)|(delete)"); 

    printb(std::regex_match("new", myAltReg)); // t
    printb(std::regex_match("delete", myAltReg)); // t
    printb(std::regex_match("malloc", myAltReg)); // f
    printb(std::regex_match("deleted", myAltReg)); // false

    // ex. d.
    std::cout << "\nEXERCISE D \n";
    
    Regex myReg3("A*"); // match 0 (empty string) or more (A, AA,..) occurences of A
    Regex myReg4("A+"); // match 1 or more occurences of A
    Regex myReg5("(\\d{2})"); // match 2 digits
    Regex myReg6("\\d{1,}"); // match 1 or more digit

    printb(std::regex_match("1", myReg3)); // f
    printb(std::regex_match("1", myReg4)); // f
    printb(std::regex_match("1", myReg5)); // f
    printb(std::regex_match("1", myReg6)); // t

    // ex. e.
    std::cout << "\nEXERCISE E \n";

    Regex rC("(\\w)*"); // match 0 or more words
    Regex rC1("(\\W)*"); // match 0 or more non-word characters
    Regex rC2("[A-Za-z0-9_]*"); // match 0 or more alphanumeric characters and underscores

    std::cout << std::regex_match("abc", rC) << '\n';  // t
    std::cout << std::regex_match("abc", rC1) << '\n';  // f
    std::cout << std::regex_match("abc", rC2) << '\n';  // t

    std::cout << std::regex_match("A12678Z909za", rC) << '\n';  // t
    std::cout << std::regex_match("A12678Z909za", rC1) << '\n';  // f
    std::cout << std::regex_match("A12678Z909za", rC2) << '\n';  // t

    std::cout << std::regex_match("!!!", rC) << '\n';  // false
    std::cout << std::regex_match("!!!", rC1) << '\n';  // true
    std::cout << std::regex_match("!!!", rC2) << '\n';  // false

    return 0;
}