// In this exercise, we use the previously created Proposition and Matrix classes to create Matrices of Propositions.
// We then perform some pair-wise logical operations on element pairs of such matrices.
// We also compare our matrix class with a std::array<std::bitset> matrix.
// Tobias Bilgeri, 03.01.2024
#pragma once
#define EXERCISE_HEADER(x) std::cout << "\n\n" << x << "\n\n";
#include "Matrix.h"
#include "Proposition.h"
#include <cassert>



// BitMap1: Partially specialized Matrix with element type Proposition
using value_type = Proposition; 
template <int NR, int NC> 
using BitMap = Matrix<value_type, NR, NC>;

// BitMap2: Array of bitsets
template <int NR, int NC> 
using BitMap2 = std::array<std::bitset<NC>, NR>;

// Utility for printing
template <int NR, int NC>
void print_bitmap2(const BitMap2<NR, NC>& bm) {
	for (const std::bitset<NC>& row : bm) {
		std::cout << row << '\n';
	}
}



// BitMap Manipulations
using BitFunction = std::function <Proposition(const Proposition&, const Proposition&)>;

template <int NR, int NC> 
BitMap<NR, NC> mask(const BitMap<NR, NC>& bm1, const BitMap<NR, NC>& bm2, const BitFunction& masker) {
	// Element wise application of binary function to two bitmaps to create new bitmap.
	// (BitMap x BitMap) -> BitMap
	// masker( bm1(i,j), bm2(i, j) ) -> ans(i, j)
	BitMap<NR, NC> ans;
	for (size_t i = 0; i != NR; i++) {
		for (size_t j = 0; j != NC; j++) {
			ans(i, j) = masker(bm1(i, j), bm2(i, j));
		}
	}
	return ans;
};

auto COND = [](const Proposition& p1, const Proposition& p2) { return p1 % p2; };
auto BICOND = [](const Proposition& p1, const Proposition& p2) { return p1 <=> p2; };
auto XOR = [](const Proposition& p1, const Proposition& p2) { return p1 ^ p2; };
auto OR = [](const Proposition& p1, const Proposition& p2) { return p1 | p2; };
auto AND = [](const Proposition& p1, const Proposition& p2) { return p1 & p2; };



// BitMap2 initialization
template <int NR, int NC>
void initialise(BitMap2<NR, NC>& bm, const int col, const std::string& s) {
	// Initialize a BitMap2 column to a specific set of values.
	assert(s.size() == bm.size());
	for (int row = 0; row != NR; row++) {
		bm[row][col] = (s.at(row) == '1');
	}
}



int main() {

	// a: BitMap, BitMap2
	EXERCISE_HEADER("exercise a");
	{
		BitMap<2, 2> bm1{ {true, false}, {false, true} };
		BitMap2<2, 2> bm2{ std::bitset<2>("10"), std::bitset<2>("01") };

		bm1.print();
		print_bitmap2<2, 2>(bm2);
	}

	// b: Apply function.
	EXERCISE_HEADER("exercise b");
	{
		BitMap<2, 2> bm1{ {true, true}, {false, false} };
		BitMap<2, 2> bm2{ {true, false}, {false, true} };
		bm1.print();
		bm2.print();

		auto bmA = mask(bm1, bm2, COND);
		auto bmB = mask(bm1, bm2, BICOND);
		auto bmC = mask(bm1, bm2, OR);
		auto bmD = mask(bm1, bm2, XOR);
		auto bmE = mask(bm1, bm2, AND);

		bmA.print();
		bmB.print();
		bmC.print();
		bmD.print();
		bmE.print();
	}

	// c: Assign values to a column.
	EXERCISE_HEADER("exercise c");
	{
		// Neither of these options is too user friendly.
		// A numpy-like syntax would be great, such as: matrix[0, 1:5] = true.

		// Initialize BitMap2
		const int P = 8; 
		const int Q = 8;
		BitMap2<P, Q> bitblt2;
		initialise<P, Q>(bitblt2, 0, std::string("01111100"));
		print_bitmap2(bitblt2);
		
		// Initialize BitMap
		BitMap<P, Q> bitblt(false);
		bitblt( 1, Q - 1) = bitblt(2, Q - 1) = bitblt(3, Q - 1) = bitblt(4, Q - 1) = bitblt(5, Q - 1) = true;
		bitblt.print();
	}

	return 0;
}