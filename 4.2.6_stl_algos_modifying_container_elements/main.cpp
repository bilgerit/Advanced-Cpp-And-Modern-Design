// In this exercise, we look at some algorithms to modify elements in a container.
// Tobias Bilgeri, 05.01.2024
#pragma once
#include <iostream>
#include <algorithm>
#include <set>
#include <array>
#include <type_traits>
#include <sstream>
#include <ostream>
#include <functional>


// Printing utility.

template<typename Container>
void printContainer(const Container& c) {
	// Print a container.
	for (const auto& el : c) {
		std::cout << el << " ";
	}
	std::cout << " \n";
}

template <typename T> 
void println(const T& out) {
	std::cout << out << "\n";
}



// Ex. b. Implementations.

class Point {
	// Simple point. 
	// Possesses x and y coordinates and some operations that can be performed on 
private:
	double x;
	double y;

public:
	Point(double x, double y) : x(x), y(y) {}

	double distance(const Point& other) const {
		// Euclidian distance
		return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
	}

	// Printing
	friend std::ostream& operator << (std::ostream& os, const Point& p) {
		os << "(" << p.x << ", " << p.y << ")";
		return os;
	}

	// Comparison operators
	bool operator == (const Point& other) const {
		// Are both coordinates equal?
		return x == other.x && y == other.y;
	}

	bool operator < (const Point& other) const {
		// Sort 2 points.
		// First tries to sort by x value.
		// If x is equal, we check y additionally.
		// Required for sorted containers such as set.
		return x < other.x || (x == other.x && y < other.y);
	}
};

void filter_points(std::set<Point>& point_set, const Point& reference_point, double max_dist) {
	// Remove points from a set<Point> which are not within maximum distance max_dist of a reference point reference_point.
	// Modifies the set<Point> container in-place.

	for (auto it = point_set.begin(); it != point_set.end(); ) {
		if (it->distance(reference_point) <= max_dist) {
			it++;
		}
		else {
			it = point_set.erase(it);
		}
	}
}



// Ex. c.
std::string trim(const std::string& str) {
	// find first and last characters that arent whitespaces (tabs, newlines, spaces).
	auto start = str.find_first_not_of(" \t\n\r");
	auto end = str.find_last_not_of(" \t\n\r");

	// if string is empty now: return whitespace
	if (start == std::string::npos) return "";

	return str.substr(start, end - start + 1);
}

std::string trim_if(const std::string& str, const std::function<bool(char)>& predicate) {
	// find 1st char that does not satisfy predicate.
	auto start = std::find_if_not(str.begin(), str.end(), predicate);
	// find last char that does not satisfy predicate.
	// makes use of rbegin, rend.
	auto end = std::find_if_not(str.rbegin(), str.rend(), predicate);

	// If string is now empty: return empty string.
	if (start == str.end()) return "";

	return std::string(start, end.base());
}

std::vector<std::string> split(const std::string& str, char delimiter) {
	// split a string according to some delimiter.
	// for example, split a string into substrings each time '\n' appears.
	// result is stored in a vector of strings.
	std::vector<std::string> result;
	std::stringstream ss(str);  // create stringstream. required for getline.
	std::string item;

	while (std::getline(ss, item, delimiter)) {
		result.push_back(item);
	}

	return result;
}

std::string join(const std::string& str_1, const std::string& str_2) {
	// concatenate two strings.
	return str_1 + str_2;
}




int main() {

	// Ex. a. Remove elements in S1 if they are not in S2.
	std::set<char> S1 = { 'a', 'b', 'c', 'd', 'e', 'k' };
	std::set<char> S2 = { 'a', 'e' };

	// Exemplary solution.
	auto is_in_S2 = [&S2](const auto& el) {return S2.find(el) != S2.end(); };

	for (auto it = S1.begin(); it != S1.end(); ) {
		if (is_in_S2(*it)) {
			++it;
		}
		else {
			it = S1.erase(it);
		}
	}
	
	println("Exercise a: Solution is ..");
	printContainer(S1);


	// Ex. b.
	std::array<Point, 5> point_array = { Point(7, 8), Point(1, 2), Point(1, 2), Point(3, 4), Point(5, 6) };

	// convert Point array to set.
	std::set<Point> point_set{point_array.begin(), point_array.end()};

	println("Exericse b: \nPoint array: ");
	printContainer(point_array);
	println("Point set: ");
	printContainer(point_set);

	// remove all points from point_set that are not within distance 2 of Point(1, 2).
	filter_points(point_set, Point(1, 2), 3);
	println("Point set after filtering w/ max_dist=3: ");
	printContainer(point_set);


	// Ex. c.
	println("Exercise c: \n");
	std::string s1 = "\n\tHello World!";
	std::string s2 = "Hello World!";

	println(trim(s1));
	println(trim_if(s2, [](char c) {return c == 'H'; }));
	println(join(s1, s2));
	for (auto& el : split(s1, ' ')) {
		println(el);
	}

	return 0;
}