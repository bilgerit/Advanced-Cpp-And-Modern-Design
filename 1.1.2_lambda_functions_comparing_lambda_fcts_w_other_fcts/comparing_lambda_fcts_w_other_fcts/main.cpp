// In this exercise, we compare the different ways of multiplying elements (accumulate + lambdas, functors, free functions).
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include <iostream>
#include <numeric>
#include <vector>
#include <complex>

#include "util.hpp"

using namespace std;

int main()
{
	// a	
	cout << "Question a" << endl;
	
	cout << "Multiplying real values: " << endl;
	int initVal{ 1 };
	vector<int> vec{ 1,2,3,4,5 };
	
	int acc_std = accumulate(vec.begin(), vec.end(), initVal,
		std::multiplies<int>());
	
	int acc_struct = accumulate(vec.begin(), vec.end(), initVal,
		FOMultiply());
	
	int acc_lambda = accumulate(vec.begin(), vec.end(), initVal,
		MyMultiply);

	cout 
		<< "using std::multiplies: " << acc_std 
		<< ", using the struct: " << acc_struct
		<< ", using the lambda fct w/ auto keyword: " << acc_lambda
		<< endl;

	// Complex numbers:
	cout << "Adding complex values: " << endl;
	using Complex = std::complex<double>; // equiv. to typedef std::complex<double> Complex;
	Complex initCVal(1.0, 1.0);
	std::vector<Complex> complexArray{Complex(1.0, 1.0), Complex(2.0, 2.0) };
	
	Complex c_acc_std = accumulate(complexArray.begin(), complexArray.end(),
		initCVal, multiplies<Complex>());
	
	Complex c_acc_struct = accumulate(complexArray.begin(), complexArray.end(),
	initCVal, FOMultiply());
	
	Complex c_acc_templ = accumulate(complexArray.begin(), complexArray.end(),
		initCVal, MyMultiply2<Complex>);
	
	Complex c_acc_lambda_auto = accumulate(complexArray.begin(), complexArray.end(),
		initCVal, MyMultiply);
	
	cout 
		<< "using std::multiplies: " << c_acc_std 
		<< ", using the struct: " << c_acc_struct 
		<< ", using the lambda fct w/ auto keyword: " << c_acc_lambda_auto
		<< ", using the templated fct: " << c_acc_templ
		<< endl;
	
	
	// b
	cout << "\nMultiply real and complex values using custom accumulator: " << endl;
	auto acc_my_acc = my_accumulate(vec.begin(), vec.end(), initVal, std::multiplies<int>());
	auto c_acc_my_acc = my_accumulate(complexArray.begin(), complexArray.end(), initCVal, std::multiplies<Complex>());
	cout << acc_my_acc << ", " << c_acc_my_acc << endl;


	// c
	cout << "\nMultiply real and complex values using custom accumulator w/ passed Lambda fct: " << endl;
	auto acc_my_acc2 = my_accumulate(vec.begin(), vec.end(), initVal, MyMultiply);
	auto c_acc_my_acc2 = my_accumulate(complexArray.begin(), complexArray.end(), initCVal, MyMultiply);
	cout << acc_my_acc2 << ", " << c_acc_my_acc2 << endl;

	system("pause");
	return 0;
}