// In this exercise, we will use the class C to demonstrate the difference between copy and move semantics.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <vector>
#include "util.h"

using namespace std;


int main()
{
	// a, b, c
	cout << "  *** (a, b, c) *** " << endl;
	C<int> c1;
	c1.print_members();

	vector<int> v = { 1, 2, 3, 4, 5 };
	C<int> c2(v);
	c2.print_members();
	c2.scale(2);
	c2.print_members();
	c1 = c2;
	c1.print_members();

	// invoke move constructor by creating rvalue via std::move
	C<int> c3{move(c1)};
	c1.print_members();
	c3.print_members();

	// invoke copy constructor by passing regular lvalue
	C<int> c4{c3};
	c3.print_members();
	c4.print_members();

	return 0;
}
