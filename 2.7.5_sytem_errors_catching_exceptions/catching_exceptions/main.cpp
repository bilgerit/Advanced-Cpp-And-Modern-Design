// The objective of this exercise is to catch a (simulated) exception thrown when setting the exception mask of an input file stream.
// Tobias Bilgeri, 30 Nov. 2023
#pragma once
#include <iostream>
#include <fstream>
#include <string>


int main() {

	std::ifstream file(std::string("DOESNOTEXIST.txt"));

	try { 
		// Set the exception mask of the file stream 
		// In this case 
		//    1) logical error on I/O operation or 
		//    2) read/write error on I/O operation 
		file.exceptions(file.failbit | file.badbit);  // set a new exception mask (| is bitwise or operator)
	} 
	catch (const std::ios_base::failure& e) 
	{ 
		std::cout << "e: typeid_name=" << typeid(e).name() << ", what=" << e.what() << ", code=" << e.code() << std::endl;

		if (e.code() == std::io_errc::stream)    // will be true (e.code() return error_code object reference)
		{  
			std::error_code e1{ e.code() };      // error_code object can be created from e.code()
			std::error_code e2{ e1 };            // error_code object can be cretaed from other error_code object.
			std::cout << "e2: value=" << e2.value() << ", message=" << e2.message() << ", category=" << e2.category().name() << std::endl;

		}
	} 
	catch (...) 
	{ 
		std::cout << "catch all\n"; 
	}

	return 0;
};