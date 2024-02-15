// Output.ixx: interface module unit
// This module contains functionality to process the serve processed
// data downstream.
// Tobias Bilgeri, 15.02.2024

export module Output;
#include <iostream>

namespace Output
{

	export void output_int(const int result)
	{
		// serve some integer result.
		std::cout << "Output: " << result << "\n";
	}

}
