// Input.ixx: interface module unit
// This module represents functionality to get input data.
// Tobias Bilgeri, 15.02.2024

// "export": makes the module interface unit exportable
export module Input;

// optional: use namespace to better mark exported features when importing
//           them somewhere.
namespace Input {

	// "export: exports this procedure / makes it importable outside of the module
	export int get_default_input()
	{
		// generate some integer 
		constexpr int input_ = 5;
		return input_;
	}

}