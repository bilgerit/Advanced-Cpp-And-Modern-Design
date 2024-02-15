// In this exercise, we create platform dependent error code using std::error_code, as opposed to std::error_condition, 
// which creates platform independent errors.
// Tobias Bilgeri, 30 Nov. 2023
#pragma once
#include <iostream>
#include <tuple>
#include <sstream>
#include <string>

using ErrorCodeTuple = std::tuple<std::string, int, std::string>;

ErrorCodeTuple getErrorCodeTuple(const std::error_code& e) {
	// Take an error_code object and return tuple (category, value, message).
	return std::make_tuple(e.category().name(), e.value(), e.message());
}

void printErrorCodeTuple(const ErrorCodeTuple& e) {
	// Print an ErrorCodeTuple object. Accepts lvalue and rvalue references.
	std::cout << "Error Code: category=" << std::get<0>(e) << ", value=" << std::get<1>(e) << ", message=" << std::get<2>(e) << std::endl;
}

int ex_a() {
	// a) Create a default error code and an error code with a platform-dependent error code value and an error category.

	// Intersting: default error code and error codes with value 0 return error codes signalling success.
	std::cout << "\n\nExercise A\n\n";

	// Default error code
	std::error_code myDefaultErrorCode{};                                // message: no error found

	std::cout << "Default Error Code: ";
	printErrorCodeTuple(getErrorCodeTuple(myDefaultErrorCode));

	// Generic category error code
	std::error_code mySpecificErrorCode1{ 0, std::generic_category() };  // message: success
	std::error_code mySpecificErrorCode2{ 1, std::generic_category() };  // message: operation not permitted

	printErrorCodeTuple(getErrorCodeTuple(mySpecificErrorCode1));
	printErrorCodeTuple(getErrorCodeTuple(mySpecificErrorCode2));

	// System category error code
	std::error_code mySpecificErrorCode3{ 0, std::system_category() };   // message: The operation completed successfully.
	std::error_code mySpecificErrorCode4{ 1, std::system_category() };   // message: Incorrect function.

	printErrorCodeTuple(getErrorCodeTuple(mySpecificErrorCode3));
	printErrorCodeTuple(getErrorCodeTuple(mySpecificErrorCode4));
	return 0;
};


int ex_b() {
	// b) Create a function that returns the following information pertaining to instances of std::error_code:
	// • Its error code(an integer).
	// • Its message(a string).
	// • The name of its category(a string).

	// Solution: See above // already used for exercise A.
	return 0;
};


int ex_c() {
	// c) Test equality/inequality of instances of std::error_code and std::error_condition using operators == and !=.
	std::cout << "\n\nExercise C\n\n";

	// Result: In this case and on my personal machine, they are all equal.

	std::error_code myErrorCode1{};
	std::error_condition myErrorCondition1{};
	std::cout << "error_code vs error_condition: Constructor={}: is equal? " << std::boolalpha << (myErrorCode1 == myErrorCondition1) << std::endl;
	//printErrorCodeTuple(getErrorCodeTuple(myErrorCode1));

	std::error_code myErrorCode2{ 1, std::system_category() };
	std::error_condition myErrorCondition2{ 1, std::system_category() };
	std::cout << "error_code vs error_condition: Constructor={1, std::system_category()}: is equal? " << std::boolalpha << (myErrorCode2 == myErrorCondition2) << std::endl;
	//printErrorCodeTuple(getErrorCodeTuple(myErrorCode2));

	std::error_code myErrorCode3{ 2, std::generic_category() };
	std::error_condition myErrorCondition3{ 2, std::generic_category() };
	std::cout << "error_code vs error_condition: Constructor={2, std::generic_category()}: is equal? " << std::boolalpha << (myErrorCode3 == myErrorCondition3) << std::endl;
	//printErrorCodeTuple(getErrorCodeTuple(myErrorCode3));

	std::error_code myErrorCode4{ 3, std::iostream_category() };
	std::error_condition myErrorCondition4{ 3, std::iostream_category() };
	std::cout << "error_code vs error_condition: Constructor={3, std::iostream_category()}: is equal? " << std::boolalpha << (myErrorCode4 == myErrorCondition4) << std::endl;
	//printErrorCodeTuple(getErrorCodeTuple(myErrorCode4));

	return 0;
};


int main() {

	ex_a();
	ex_b();
	ex_c();

	return 0;
};