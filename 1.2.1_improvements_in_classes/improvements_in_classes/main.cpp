// In this exercise we demonstrate modern ways to make better classes.
// This includes using keywords: constexpr, noexcept, delete, default, explicit. 
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <vector>
#include "util.h"


int main()
{
	using namespace std;

	{
		cout << "Original Class: " << endl;
		C<int> c1;
		c1.print_members();

		vector<int> v = { 1, 2, 3, 4, 5 };
		C<int> c2(v);
		c2.print_members();
		c2.scale(2);
		c2.print_members();
		c1 = c2;
		c1.print_members();
	}

	{
		cout << "Improved Class: " << endl;
		CImproved<int> c1;
		c1.print_members();

		vector<int> v = { 1, 2, 3, 4, 5 };
		CImproved<int> c2(v);
		c2.print_members();
		c2.scale(2);
		c2.print_members();
	}

	return 0;
}
