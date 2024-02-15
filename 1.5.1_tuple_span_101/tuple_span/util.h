// Helper file containing utility needed for this exercise: Printing, sorting, getting specific elements, etc.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <tuple>
#include <string>
#include <algorithm>
#include <vector>
#include "boost/date_time/gregorian/gregorian_types.hpp"
#include <cassert>

using date = boost::gregorian::date;
using personTpl = std::tuple<std::string, std::string, date>;


void print_personTpl(const personTpl& person)
{
	date dob = std::get<2>(person);
	std::cout << "(First Name: " << std::get<0>(person) << ", Last Name: " << std::get<1>(person)
		 << ", Date of Birth: " << dob.year() << "-" << dob.month() << "-" << dob.day() << ")" << std::endl;
}

template<typename T>
void print_container_of_personTpl(const T& container)
{
	for (auto el : container)
	{
		print_personTpl(el);
	}
	std::cout << std::endl;
}

template <int sort_index>
bool sort_container_of_personTpl(personTpl& lhs, personTpl& rhs)
{
	return get<sort_index>(lhs) < get<sort_index>(rhs);
};

template <typename T>
void print_span(const std::span<T>& span)
{
	for (auto el : span)
	{
		std::cout << el << " ";
	}
	std::cout << std::endl;
}


template <typename T>
void print_span_range(const std::span<T>& span)
{
	std::cout << "Range based printing function of the span:" << std::endl;
	for (auto el : span)
	{
		std::cout << el << " ";
	}
	std::cout << std::endl;
}

template <typename T>
void print_span_iterator(const std::span<T>& span)
{
	std::cout << "Iterator based printing function of the span:" << std::endl;
	for (auto it = span.begin(); it != span.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

template <typename T>
void print_span_indexing(const std::span<T>& span)
{
	std::cout << "Indexing based printing function of the span:" << std::endl;
	for (int i = 0; i < span.size(); i++)
	{
		std::cout << span[i] << " ";
	}
	std::cout << std::endl;
}

template <typename T>
auto* get_first_last(const std::span<T>& s, int k)
{
	std::span<T> k_first = s.subspan(0, k);
	std::span<T> k_last = s.subspan(s.size() - k, k);
	auto* elements = new T[2 * k];
	for (int i = 0; i < k; i++)
	{
		elements[i] = k_first[i];
		elements[i + k] = k_last[i];
	}
	return elements;
}

void print_array(auto& arr, int& size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void test_subspan()
{
	std::cout << "Starting to test subspan ... " << std::endl;
	const int size = 5;
	const int start = 1;
	const int end = 3;

	int array[size];
	
	for (int i = 0; i < size; i++)
	{
		array[i] = i;
	}

	std::span<int> s(array, size);
	std::span<int> subspan = s.subspan(start, end);
	
	for (int i = start; i < start+end; i++)
	{
		assert(array[i] == subspan[i - start]);
		std::cout << "array[" << i << "] = " << array[i] << " == " << "subspan[" << i - start << "] = " << subspan[i - start] << std::endl;
	}

	std::cout << "Subspan test passed!" << std::endl;
}
