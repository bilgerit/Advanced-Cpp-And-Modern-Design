// Simple header file containing utility needed for this exercise.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
# include <algorithm>

using namespace std;

// Exercise a

// Lambda Function w/ auto types for multiplying two elements.
auto MyMultiply = [](auto x, auto y) { return x * y; };

// Templated Function to multiply two elements.
template <typename T>
T MyMultiply2(const T& x, const T& y) { return x * y; };

// (Functor) Templated Structure w/ operator overloading for multiplying two elements.
struct FOMultiply
{
	template <typename T>
	T operator () (const T& x, const T& y) const
	{
		return x * y;
	}
};


// Exercise b
template <typename InputIterator, typename T, typename Fct>
T my_accumulate(InputIterator first, InputIterator last, T init, Fct fct)
{
	// my_accumulate implemented s.t. it accepts function objects (e.g. Functor, Lambda).
	// embedded lambda is used in for_each
    for_each(
		first, 
		last, 
		[&init, &fct](const auto& x) 
		{
			init = fct(init, x); 
		}
	);
    return init;
}