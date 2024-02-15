// In this exercise, we continue to explore various error conditions, their values, categories and messages, and how to construct them.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <iostream>
#include <tuple>
#include <string>

int ex_a() {
	// Create instances of std::error_condition based on the following requirements:
	// • Default constructor.
	// • Value(stored error code) and error category.
	// • Based on std::errc code.

	std::cout << "Exercise A. Construct error conditions in various ways." << std::endl;

	std::error_condition default_constructed{};
	std::error_condition custom_constructed{ 1, std::generic_category() };
	std::error_condition errc_constructed{ std::errc::bad_message };

	std::cout << "default_constructed: value=" << default_constructed.value() << ", category=" << default_constructed.category().name() << ", message=" << default_constructed.message() << std::endl;
	std::cout << "custom_constructed: value=" << custom_constructed.value() << ", category=" << custom_constructed.category().name() << ", message=" << custom_constructed.message() << std::endl;
	std::cout << "errc_constructed: value=" << errc_constructed.value() << ", category=" << errc_constructed.category().name() << ", message=" << errc_constructed.message() << std::endl;
	return 0;
};

std::tuple<std::string, int, std::string> getErrorConditionTuple(const std::error_condition& erc)
{
	return std::make_tuple(erc.message(), erc.value(), erc.category().name());
}

int ex_b() {
	// Create a function that returns the following information pertaining to instances of std::error_condition:
	// • Its error code(an integer).
	// • Its message(a string).
	// • The name of its category(a string).

	std::cout << "\n\nExercise B. Getting error code, mesage and name of error via a custom function." << std::endl;

	std::error_condition errc_constructed{ std::errc::bad_message };
	auto [err_message, err_value, err_category] = getErrorConditionTuple(errc_constructed);
	std::cout << "errc_constructed: value=" << err_value << ", category=" << err_category << ", message=" << err_message << std::endl;

	return 0;
};

int main() {
	ex_a();
	ex_b();

	return 0;
};