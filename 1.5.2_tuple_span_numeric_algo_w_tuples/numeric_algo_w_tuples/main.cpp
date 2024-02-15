// In this exercise, we perform computations on tuples using variadic member functions.
// Tobias Bilgeri, 18 Nov. 2023
#pragma once
#include "util.h"
#include <complex>
using cplx = std::complex<double>;

void ex_b() {
	std::tuple<double, double> t2 = std::make_tuple(2., 3.);
	std::tuple<double, double, double> t3 = std::make_tuple(2., 3., 4.);

	Calculator<double, std::tuple<double, double>, 2> c2;
	Calculator<double, std::tuple<double, double, double>, 3> c3;

	std::cout << "sum: " << c2.sum(t2) << ", average: " << c2.average(t2) << ", maximum: " << c2.maximum(t2) << std::endl;
	std::cout << "sum: " << c3.sum(t3) << ", average: " << c3.average(t3) << ", maximum: " << c3.maximum(t3) << std::endl;
}

void ex_c() {
	/* 
	Why does this initialization not work (all the imaginary parts get set to zero)?
	tuple<c, c, c> t3 = make_tuple((2, 2), (3, 3), (4, 4));
	*/
	cplx n1(2, 2), n2(3, 3), n3(4, 4);
	std::tuple<cplx, cplx, cplx> t3 = std::make_tuple(n1, n2, n3);

	Calculator<cplx, std::tuple<cplx, cplx, cplx>, 3> c3;

	std::cout << "sum: " << c3.sum(t3) << ", average: " << c3.average(t3) << std::endl;
}

int main()
{
	ex_b();
	ex_c();
	return 0;
}
