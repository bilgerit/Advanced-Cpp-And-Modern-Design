// In this exercise, we look at boost's string algorithms for simple string processing.
// Tobias Bilgeri, 23.01.2024
#pragma once
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>

int main() {
    std::string str1 = "   Hello World   ";
    std::string str2 = str1;
    std::string str3 = "AAAHello WorldAAA";
    std::string str4 = "Hello World";
    std::string str5 = "Hello World";

    // ex. a. trim leading & trailing blanks

    // in-place modification
    boost::trim(str1);  
    std::cout << str1 << std::endl;

    // copy
    std::string str2_trimmed = boost::trim_copy(str2);
    std::cout << str2_trimmed << std::endl;

    // ex. b. conditional trim
    boost::trim_if(
        str3, 
        boost::is_any_of("A"));

    std::cout << str3 << std::endl;

    // ex. c. test if a string starts or ends with a given string
    // case sensitive:       istarts_with
    //                       iends_with
    // case insensitive:     starts_with
    //                       ends_with
    bool starts_with_hello = boost::starts_with(str4, "Hello"); 
    bool ends_with_world = boost::iends_with(str4, "WORLD!");
    std::cout << std::boolalpha << starts_with_hello << ", " << ends_with_world << std::endl;

    // ex. d. test if a string contains another string & whether two strings are equal.
    bool contains_world = boost::contains(str4, "World");  // Case-sensitive
    bool contains_world_ci = boost::icontains(str4, "WORLD");  // Case-insensitive
    std::cout << std::boolalpha << contains_world << ", " << contains_world_ci << std::endl;

    // test string equality
    // case sensitive/insensitvie: equals, iequals
    bool are_equal = boost::iequals(str4, str5); 
    std::cout << std::boolalpha << are_equal << std::endl;

    return 0;
}