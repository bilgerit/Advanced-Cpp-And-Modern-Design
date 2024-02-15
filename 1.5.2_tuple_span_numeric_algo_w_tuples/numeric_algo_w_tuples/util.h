// Simple helper file containing utility needed for this exercise.
// Specifically, we implement a Calculatur using variadic functions.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <tuple>


template<typename T, typename Tuple, size_t N>
struct Calculator
{
	static T sum(const Tuple& t)
	{
		/* 
		Why does this not work to terminate the recursion?
		if (N == (size_t) 1)
		{
			return get<0>(t);
		}
		*/
		return std::get<N - 1>(t) + Calculator<T, Tuple, N - 1>::sum(t);
	}

	static T average(const Tuple& t)
	{
		return sum(t) / (T) N;
	}

	static T maximum(const Tuple& t)
	{
		return std::get<N - 1>(t) > Calculator<T, Tuple, N - 1>::maximum(t) ?
			std::get<N - 1>(t) : Calculator<T, Tuple, N - 1>::maximum(t);
	}
};


template<typename T, typename Tuple>
struct Calculator<T, Tuple, 1>
{
	static T sum(const Tuple& t)
	{
		return get<0>(t);
	}
	static T maximum(const Tuple& t)
	{
		return get<0>(t);
	}
};
