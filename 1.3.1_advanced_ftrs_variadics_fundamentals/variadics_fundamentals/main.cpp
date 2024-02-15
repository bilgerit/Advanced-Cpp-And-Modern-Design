// In this exercise, we create a simple variadic function for printing sets of variables.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <bitset>
#include "util.h"

using namespace std;


int main()
{
	int j = 1; double d = 2.0;
	print(j); 
	print(d); 
	print(j, d); 
	print(d, j);
	print(j, d, bitset<8>(233));

	return 0;
};