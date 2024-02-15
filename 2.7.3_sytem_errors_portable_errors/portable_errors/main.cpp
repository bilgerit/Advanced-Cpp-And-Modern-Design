// In this exercise, we explore how to produce different error conditions, their messages and categories.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <iostream>
#include <string>


int ex_a() {
	/* Create error condition instances based on the following POSIX error codes (use scoped enumerator std::errc ):
	• io_error.
	• network_unreachable.
	• no_such_file_or_directory.
	• not_a_socket.
	• permission_denied.
	*/
	std::error_condition io_error{ std::errc::io_error };
	std::error_condition network_unreachable{ std::errc::network_unreachable };
	std::error_condition no_such_file_or_directory{ std::errc::no_such_file_or_directory };
	std::error_condition not_a_socket{ std::errc::not_a_socket };
	std::error_condition permission_denied{ std::errc::permission_denied };

	std::cout << "io_error: message=" << io_error.message() << std::endl;
	std::cout << "network_unreachable: message=" << network_unreachable.message() << std::endl;
	std::cout << "no_such_file_or_directory: message=" << no_such_file_or_directory.message() << std::endl;
	std::cout << "not_a_socket: message=" << not_a_socket.message() << std::endl;
	std::cout << "permission_denied: message=" << permission_denied.message() << std::endl;

	return 0;
};


int ex_b() {
	std::error_condition error_128{ 128, std::generic_category() };
	std::cout << "error_128: message=" << error_128.message() << ", category=" << error_128.category().name() << std::endl;

	return 0;
};


int ex_c() {
	std::error_condition io_error = std::make_error_condition(std::errc::io_error);
	std::cout << "io_error: message=" << io_error.message() << ", category=" << io_error.category().name() << std::endl;

	return 0;
};


int main() {

	ex_a();
	ex_b();
	ex_c();

	return 0;
};