// In this exercise, we demonstrate tuples and spans.
// Spans are views of subsets of containers and allows dealing with these subsets without copying the underlying data.
// Tuples are containers of often heterogeneous types and are extremely useful in for example structured bindings, or generally when you need to handle multiple 
// different data types in specific sequences.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <span>
#include <iomanip>
#include "util.h"


void exercise_a_to_c()
{
	// a
	personTpl person = std::make_tuple("John", "Doe", date(1980, 1, 1));
	std::cout << "initial person: " << std::endl;
	print_personTpl(person);
	get<2>(person) = date(1981, 1, 2);
	std::cout << "initial person after change birthdate: " << std::endl;
	print_personTpl(person);

	// b
	// (see above, and util.h)

	// c
	std::vector<personTpl> persons;
	for (int i = 0; i < 5; i++)
	{
		std::string first_name = "John the " + std::to_string(i);
		persons.push_back(make_tuple(first_name, "Doe", date(1980 - i, 1, 1)));
	}

	// d
	// here: sort by 3rd column (i.e., date)
	std::cout << "\n\nvector of persons before sorting: " << std::endl;
	print_container_of_personTpl(persons);
	sort(persons.begin(), persons.end(), sort_container_of_personTpl<2>);
	std::cout << "\nvector of persons after sorting: " << std::endl;
	print_container_of_personTpl(persons);
}

void exercise_e_to_h()
{
	// e
	int fixedArray[5] = { 1, 2, 3, 4, 5 };
	std::span<int, 5> fixedSpan(fixedArray);

	int size = 3;
	int* dynamicArray = new int[size] {6, 7, 8};
	std::span<int> dynamicSpan(dynamicArray, size);

	std::cout << "Fixed Span: ";
	print_span<int>(fixedSpan);

	std::cout << "Dynamic Span: ";
	print_span<int>(dynamicSpan);

	fixedSpan[0] = 10;
	dynamicSpan[2] = 20;

	std::cout << "Modified Fixed Span: ";
	print_span<int>(fixedSpan);

	std::cout << "Modified Dynamic Span: ";
	print_span<int>(dynamicSpan);

	std::cout << "... as shown here, we can modify both the fixed size and variable size arrays." << std::endl << std::endl;

	delete[] dynamicArray;

	// f
	print_span_range<int>(fixedSpan);
	print_span_iterator<int>(fixedSpan);
	print_span_indexing<int>(fixedSpan);

	// g
	std::cout << std::endl;
	int k = 3;
	int array_size = 2 * k;
	std::cout << "Fetching " << k << " first and last elements" << std::endl;
	int* elements = get_first_last<int>(fixedSpan, k);
	print_array(elements, array_size);
	delete[] elements;

	k = 2;
	array_size = 2 * k;
	std::cout << "Fetching " << k << " first and last elements" << std::endl;
	int* elements2 = get_first_last<int>(fixedSpan, k);
	print_array(elements2, array_size);
	delete[] elements2;

	// h
	std::cout << std::endl;
	test_subspan();
	std::cout << std::endl;
}

void exercise_i()
{
	float data[1]{ 3.141592f };

	// Create a const byte view of the span
	auto const const_bytes = std::as_bytes(std::span{ data });
	for (auto const b : const_bytes)
	{
		std::cout << std::setw(2)
			<< std::hex
			<< std::uppercase
			<< std::setfill('0')
			<< std::to_integer<int>(b) << ' ';
	}

	// Create a writable byte view of the span
	auto writable_bytes = std::as_writable_bytes(std::span{ data });
	for (auto& b : writable_bytes) {
		b = static_cast<std::byte>(0xFF);  // Modify the bytes
	}

	// Print the modified bytes
	for (auto const b : const_bytes) {
		std::cout << std::setw(2)
			<< std::hex
			<< std::uppercase
			<< std::setfill('0')
			<< to_integer<int>(b) << ' ';
	}
	std::cout << std::endl;
}

int main()
{
	exercise_a_to_c();
	exercise_e_to_h();
	exercise_i();

	system("pause");
	return 0;
};