// Binary Classification of strings
// Tobias Bilgeri, 23.01.2026
#include <iostream>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

using String = std::string;

std::pair<bool, String> checkPassword(const String& pwd) {
    // Simple password checker created using the standard library.
    // Performs a binary classification.
    // Return: pair of (BOOL_ANSWER, STR_ANSWER)
    if (pwd.size() < 8) {
        return { false, "Password must contain at least 8 characters." };
    }

    if (!std::ranges::any_of(pwd, ::isdigit) || !std::ranges::any_of(pwd, ::isalpha)) {
        return { false, "Password must contain a combination of digits and characters." };
    }
    if (!std::ranges::any_of(pwd, ::isupper)) {
        return { false, "Password must contain at least one upper case character." };
    }
    if (std::ranges::any_of(pwd, ::iscntrl)) {
        return { false, "Password must not contain control characters." };
    }
    if (std::ranges::any_of(pwd, ::isspace)) {
        return { false, "Password must not contain spaces." };
    }
    return { true, "Password is valid." };
}

int main() {
    // ex. a. 
    String s = "abd1 234\*";
    
    // P1: s consists only of numbers, letters and spaces.
    bool p1 = std::ranges::all_of(
        s,
        [](char c) { return ::isdigit(c) || ::isalpha(c) || ::isspace(c); });
    
    // P2: s consists only of numbers and spaces, but no letters.
    bool p2 = std::ranges::all_of(
        s,
        [](char c) { return ::isdigit(c) || ::isspace(c); });

    // P3: s consists only of letters between.
    bool p3 = std::ranges::all_of(
        s,
        [](char c) { return c >= 'a' && c <= 'z'; });

    std::cout << "ex. a.: Predicates P1, P2, P3: " << std::boolalpha << p1 << " " << p2 << " " << p3 << "\n";

    // ex. b. password checker.
    String pwd1("DanielDuffy1952");
    String pwd2("DanielDuffy");
    String pwd3("U19520829");
    String pwd4("19520829U");
    String pwd5("short");
    String pwd6("lowercaseonly1");
    String pwd7("1234567890");

    auto result1 = checkPassword(pwd1);
    std::cout << result1.second << '\n';

    auto result2 = checkPassword(pwd2);
    std::cout << result2.second << '\n';

    auto result3 = checkPassword(pwd3);
    std::cout << result3.second << '\n';

    auto result4 = checkPassword(pwd4);
    std::cout << result4.second << '\n';

    auto result5 = checkPassword(pwd5);
    std::cout << result5.second << '\n';

    auto result6 = checkPassword(pwd6);
    std::cout << result6.second << '\n';

    auto result7 = checkPassword(pwd7);
    std::cout << result7.second << '\n';

    return 0;
}