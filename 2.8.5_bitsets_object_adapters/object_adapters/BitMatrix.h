// BitMatrix class
// The BitMatrix class implements a std::array with elements of type std::bitset (= 'matrix').
// The number of rows and cols are brought in at compile time as template arguments.
// The class reimplements std::bitset methods such as .any(), .all(), .flip(), .set(), bitwise logic operations, etc., on a whole-matrix level, 
// while still allowing row-wise operations.
// Tobias Bilgeri, 1. Dec. 2023
#pragma once
#include <iostream>
#include <bitset>
#include <tuple>
#include <array>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>


template<size_t M, size_t N>
class BitMatrix {
	// BitMatrix: An array of bitsets.
	// Reimplements std::bitset logic but on a matrix level.
	// 
	// Template Args:
	//		M: number of rows
	//		N: num of columns
private:
	std::array<std::bitset<N>, M> bitMatrix;

public:

	BitMatrix<M, N>() = default;
	BitMatrix<M, N>(const BitMatrix<M, N>& other) = default;
	BitMatrix<M, N>(BitMatrix<M, N>&& other) noexcept {
		for (int i = 0; i != M; i++) {
			std::swap(bitMatrix[i], other.bitMatrix[i]);
		}
	};
	~BitMatrix<M, N>() = default;

	BitMatrix<M, N>& operator = (const BitMatrix<M, N>& other) {
		*this = BitMatrix<M, N>(other);
		return *this;
	}

	BitMatrix<M, N>& operator = (BitMatrix<M, N>&& other) noexcept {
		// Move assignment
		for (int i = 0; i != M; i++) {
			std::swap(bitMatrix[i], other.bitMatrix[i]);
		}
		return *this;
	}

	std::string to_string() const {
		std::stringstream ss;
		ss << "[";
		for (int i = 0; i != M; i++) {
			ss << "\n[";
			ss << bitMatrix[i];
			ss << "]";
		}
		ss << "\n]";
		return ss.str();
	}

	void print() const {
		std::cout << this->to_string() << std::endl;
	}

	// Getters

	std::bitset<N> get(const int& row) const {
		return bitMatrix[row];
	}

	bool get(const int& row, const int& col) const {
		return bitMatrix[row][col];
	}

	// Row-wise operations.

	void set(const int& row, const std::bitset<N>& b) {
		bitMatrix[row] = b;
	}

	void set(const int& row) {
		bitMatrix[row].set();
	}
	
	void reset(const int& row) {
		bitMatrix[row].reset();
	}

	void flip(const int& row) {
		bitMatrix[row].flip();
	}

	bool none(const int& row) const {
		return bitMatrix[row].none();
	}

	bool all(const int& row) const {
		return bitMatrix[row].all();
	}

	bool any(const int& row) const {
		return bitMatrix[row].any();
	}

	size_t count(const int& row) const {
		return bitMatrix[row].count();
	}

	// matrix-wise operations.

	void set() {
		std::ranges::for_each(bitMatrix.begin(), bitMatrix.end(), [](std::bitset<N>& b) { b.set(); });
	}

	void reset() {
		std::ranges::for_each(bitMatrix.begin(), bitMatrix.end(), [](std::bitset<N>& b) { b.reset(); });
	}

	void flip() {
		std::ranges::for_each(bitMatrix.begin(), bitMatrix.end(), [](std::bitset<N>& b) { b.flip(); });
	}

	bool none() const {
		return std::ranges::all_of(bitMatrix.begin(), bitMatrix.end(), [](std::bitset<N> b) { return b.none(); });
	}

	bool all() const {
		return std::ranges::all_of(bitMatrix.begin(), bitMatrix.end(), [](std::bitset<N> b) { return b.all(); });
	}

	bool any() const {
		return std::ranges::any_of(bitMatrix.begin(), bitMatrix.end(), [](std::bitset<N> b) { return b.any(); });
	}

	int count() const {
		return std::accumulate(bitMatrix.begin(), bitMatrix.end(), 0, [](int sum, const std::bitset<N>& b) { return sum + b.count(); });
	}

	// two-matrices operation.

	BitMatrix<M, N> OR(const BitMatrix<M, N>& arg) const {
		BitMatrix<M, N> ans;
		for (int i = 0; i != M; i++) {
			ans.set(i, bitMatrix[i] | arg.get(i));
		}
		return ans;
	}

	BitMatrix<M, N> XOR(const BitMatrix<M, N>& arg) const {
		BitMatrix<M, N> ans;
		for (int i = 0; i != M; i++) {
			ans.set(i, bitMatrix[i] ^ arg.get(i));
		}
		return ans;
	}

	BitMatrix<M, N> AND(const BitMatrix<M, N>& arg) const {
		BitMatrix<M, N> ans;
		for (int i = 0; i != M; i++) {
			ans.set(i, bitMatrix[i] & arg.get(i));
		}
		return ans;
	}
};
