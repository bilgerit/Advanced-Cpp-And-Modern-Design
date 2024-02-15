// Classifying algorithms
// We create a Stack-Wrapper with some special methods.
// Methods are (i) reducing, (ii) generating, (iii) permutating.
// Tobias Bilgeri, 05.01.2024
#pragma once
#include "StackADT.h"



int main() {
	// max, min, drop: reduction 
	// over: generation
	// rot, swap: permutation

	StackADT<int> s;
	s.native.push(1);
	s.native.push(2);
	s.native.push(3);
	s.native.push(4);
	s.native.push(5);
	s.native.push(6);
	s.native.push(7);
	s.native.push(8);
	s.print();
	
	println("calling drop: ");
	s.drop();
	s.print();

	println("calling over: ");
	s.over();
	s.print();

	println("calling max: ");
	s.max();
	s.print();

	println("calling min: ");
	s.min();
	s.print();

	println("calling rot: ");
	s.rot();
	s.print();

	println("calling swap: ");
	s.swap();
	s.print();

	return 0;
}