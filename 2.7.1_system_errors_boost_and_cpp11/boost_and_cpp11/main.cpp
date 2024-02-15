// In this exercise, we try to give platform independent error conditions
// using Boost and STL. STL implementation seems to be based on ported Boost code.
// Tobias Bilgeri, 19 Nov. 2023
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <boost/system/error_condition.hpp>

// Test file paths:
std::string FILE_PATH{ "test.txt" };
std::string NONEXISTANT_FILE_PATH{ "NONEXISTANT_FILE.txt" };

boost::system::error_condition ReadFileBoostError(const std::string& filePath) 
{
	// Read a file and print every line.
	// Return type is boost error condition.

	std::ifstream f{ filePath };
	
	if (!f)
	{
		std::cout << "File " << filePath << " could not be opened." << std::endl;

		// Note: I should be using make_error_condition here.
		//       But the code seems to have changed in boost 1.83.0.
		//       Using plain error_condition instead.
		return boost::system::error_condition{ boost::system::errc::no_such_file_or_directory };
	}

	std::string line;
	while (std::getline(f, line)) 
	{
		std::cout << line << std::endl;
	}

	f.close();
	return boost::system::error_condition{};
};

std::error_condition ReadFileSTLError(const std::string& filePath)
{
	// Read a file and print every line.
	// Return type is boost error condition.

	std::ifstream f{ filePath };

	if (!f)
	{
		std::cout << "File " << filePath << " could not be opened." << std::endl;

		// Note: I should be using make_error_condition here.
		//       But the code seems to have changed in boost 1.83.0.
		//       Using plain error_condition instead.
		return std::error_condition{ std::errc::no_such_file_or_directory };
	}

	std::string line;
	while (std::getline(f, line))
	{
		std::cout << line << std::endl;
	}

	f.close();
	return std::error_condition{};
};

int ex_c() {
	// Read & print file if it exists. Handle errors w/ Boost.

	std::cout << "Exercise C. Make use of Boost to handle errors.\n";

	auto res_a = ReadFileBoostError(FILE_PATH);
	std::cout << "Result a: " << res_a.message() << std::endl;

	auto res_b = ReadFileBoostError(NONEXISTANT_FILE_PATH);
	std::cout << "Result b: " << res_b.message() << std::endl;
	return 0;
};


int ex_d() {
	// Read & print file if it exists. Handle errors w/ STL.

	std::cout << "\n\nExercise D. Make use of STL instead for handling errors.\n";

	auto res_a = ReadFileSTLError(FILE_PATH);
	std::cout << "Result a: " << res_a.message() << std::endl;

	auto res_b = ReadFileSTLError(NONEXISTANT_FILE_PATH);
	std::cout << "Result b: " << res_b.message() << std::endl;
	return 0;
	return 0;
};


int main() {

	ex_c();
	ex_d();

	return 0;
};