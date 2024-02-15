// Processing.ixx: interface module unit
// This module contains functionality to process the inputs obtained
// form the Input module.
// Tobias Bilgeri, 15.02.2024

export module Processing;

int process_int_hidden(const int input)
{
	// process integer input
	// don't export this
	return input * input;
}

// optional: use namespace to better mark exported features when importing
//           them somewhere.
 namespace Processing {

	export int process_int(const int input)
	{
		// process integer input
		return process_int_hidden(input);
	}

}