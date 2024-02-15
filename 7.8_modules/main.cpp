// Modules
//
// In this exercise, we take some initial look at 
// 
// Tobias Bilgeri, 05.01.2024

// Question a) Modular design and Single Responsibility Principle (SRP).
// Each module ideally has a single responsibility. The module herein can be an alternative to namespaces, with added functionality.
// Furthermore, modules allow to expose only specific parts of code to a client, thus allowing for better API design in closed-source software.

// Question b) C++ modules and header files living side by side.
// C++ modules and header files can live side by side, hence we maintain backwards compatibility (as C++ pretty much always does).

// Question c) Support for Information Hiding.
// In modules, only entities that are explicitly exported are accessible from other modules.
// This allows to better expose entities we want to expose, and hide entities we don't want to expose.

// Question d) Less dependencies than using header files.
// Header files are usually preprocessed, parsed, and compiled for each .cpp file containing them.
// Module interfaces go through this process only once. This may greatly improve compilation times.
// Also, incremental compilation with modules is improved compared to header files. For the latter, the compiler has to recompile every
// translation unit which makes use of the header file.

#pragma once

// Code Example
import Input;
import Processing;
import Output;

int main() {
    const int input = Input::get_default_input();
    const int result = Processing::process_int(input);
    Output::output_int(result);
    return 0;
}
