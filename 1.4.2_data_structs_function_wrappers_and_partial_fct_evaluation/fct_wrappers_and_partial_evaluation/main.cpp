// In this exercise, we demonstrate partial evaluation.
// Partial function evaluation is implemented with std::bind and std::placeholder.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include "util.h"
using namespace std;


int main()
{
	int x{ 1 }, y{ 1 }, z{ 1 };
	cout << freeFunction3(x, y, z) << endl;
	cout << freeFunction2(x, y) << endl;
	cout << freeFunction1(x) << endl;
	cout << freeFunction0() << endl;
	return 0;
}