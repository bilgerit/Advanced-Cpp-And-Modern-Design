// In this exercise, we take a look at the forward_list. It is based on a singly linked
// list and supports various methods such as merge, spline, insertion, etc.,
// , but no random access based operations.
// Tobias Bilgeri, 13. Dec. 2023
#pragma once
#include <iostream>
#include <forward_list>
#include <algorithm>




int main() {
	// Exericse a) different ways to initialize
	std::forward_list<int> fl1{};
	std::forward_list<int> fl2(5, 1);
	std::forward_list<int> fl3{ 1, 2, 3, 4, 5 };



	// Exercise b) function to compute list lenght
	auto getForwardListSize = [](std::forward_list<int>& fl) -> size_t { return std::distance(fl.begin(), fl.end()); };
	std::cout << getForwardListSize(fl3) << std::endl;


	// Exercise c) various ways to insert values.
	auto it = fl3.begin();

	// Insert value after n'th index:
	// Note: Can't use fl3.begin()+2 since this only works if you have random access, which a singly linked list doesn't support. 
	const int n = 2;
	const int val = 3;
	std::advance(it, n);  
	fl3.insert_after(it, val);
	for (const auto& el : fl3) { std::cout << el; }
	std::cout << "\n";

	// Insert value after n'th index, cnt times:
	const int cnt = 3;
	fl3.insert_after(it, cnt, val);
	for (const auto& el : fl3) { std::cout << el; }
	std::cout << "\n";

	// Insert values from a different list using pointers:
	// Note: instead of creating pointer and applying std::advance on the new object, I now just use std::next(fl2.begin(), n);
	fl3.insert_after(it, fl2.begin(), std::next(fl2.begin(), 2));  
	for (const auto& el : fl3) { std::cout << el; }
	std::cout << "\n";

	// Insert from initializer list
	fl3.insert_after(it, { 11, 22, 33 });
	for (const auto& el : fl3) { std::cout << el; }
	std::cout << "\n";



	// Exercise d) functions to erase after an index, or between a range of iterators.

	// Erase after index:
	// will erase element w/ index 1.
	const int idx_erase = 1;  
	fl3.erase_after(std::next(fl3.begin(), idx_erase - 1));
	for (const auto& el : fl3) { std::cout << el; }
	std::cout << "\n";

	// Erase between range of iterators: 
	// Will erase elements between fl3.begin() and fl3.begin()+2
	// Note that bounds here are exclusive, hence we erase only 1 element.
	fl3.erase_after(fl3.begin(), std::next(fl3.begin(), 2));
	for (const auto& el : fl3) { std::cout << el; }
	std::cout << "\n";



	// Exercise e) examples of splicing and merge.

	// Merge: requires either (i) both lists sorted, or (ii) comparator; see geeksforgeeks.org/forward_list-merge-in-c-stl/
	std::forward_list<int> fl4 = { 1, 3, 5 };
	std::forward_list<int> fl5 = { 2, 4 , 6 };
	fl4.merge(fl5);  // 1, 2, 3, 4, 5, 6
	for (const auto& el : fl4) { std::cout << el; }
	std::cout << "\n";

	// Splice: just inserts one list into another at a given position.
	std::forward_list<int> fl6 = { 0, 7 };
	fl4.splice_after(std::next(fl4.begin(), 1), fl6);
	for (const auto& el : fl4) { std::cout << el; }
	std::cout << "\n";

	return 0;
};