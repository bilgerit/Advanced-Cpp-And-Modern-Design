// In this exercise we look at move semantics, and how it helps to speed up many operations.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "util.h"

using namespace std;


int main()
{
	// a
	cout << "\n  *** (a) *** \n" << endl;
	string s1{ "mystring" };
	string s2;
	cout << "s1: " << s1 << ", s2: " << s2 << endl;
	s2 = move(s1);
	cout << "s1: " << s1 << ", s2: " << s2 << endl;


	// b
	cout << "\n  *** (b) *** \n" << endl;
	vector <int> v1{ 1, 2, 3, 4, 5 };
	vector <int> v2;
	cout << "v1: " << vec_to_string(v1) << ", v2: " << vec_to_string(v2) << endl;
	v2 = move(v1);
	cout << "v1: " << vec_to_string(v1) << ", v2: " << vec_to_string(v2) << endl;

	// compare timings: copy vs move
	vector <int> v3, v4, v5;
	auto start = chrono::high_resolution_clock::now();
	v3 = move(v2);
	auto end = chrono::high_resolution_clock::now();
	cout << "move took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
	start = chrono::high_resolution_clock::now();
	v4 = v3;
	end = chrono::high_resolution_clock::now();
	cout << "assignement took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
	start = chrono::high_resolution_clock::now();
	v5 = v4;
	end = chrono::high_resolution_clock::now();
	cout << "copy took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;

	
	// c
	cout << "\n  *** (c) *** \n" << endl;
	vector<int> w1{1, 2, 3};
	vector<int> w2{1, 2, 3, 4, 5};
	cout << "using the following vectors to study the durations of copy and move: " 
		<< vec_to_string(w1) << ", " << vec_to_string(w2) << endl;
	start = chrono::high_resolution_clock::now();
	SwapCopyStyle(w1, w2);
	end = chrono::high_resolution_clock::now();
	cout << "copy took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
	start = chrono::high_resolution_clock::now();
	SwapMoveStyle(w1, w2);
	end = chrono::high_resolution_clock::now();
	cout << "move took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;

	return 0;
};