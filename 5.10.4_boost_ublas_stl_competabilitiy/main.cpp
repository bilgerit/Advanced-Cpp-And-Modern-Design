// Boost-ublas and STL competability
// 
// Playing around with some algorithms in std::algorithm to achieve equal 
// functionalitiy.
// Used in combination with boost-ublas-vectors.
// 
// Tobias Bilgeri, 2024.01.31

#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

#include <iostream>
#include <boost/numeric/ublas/vector.hpp>
#include <algorithm>
#include <vector>

using Vector = boost::numeric::ublas::vector<double>;
using Range = std::tuple<std::size_t, std::size_t>; 
using Result = std::tuple<Range, bool>;


Result find_sequential_greater_g(const Vector& v, Vector::value_type x) {
    // given function
    // tries to find two consecutive elements for which v(i) <= x < v(i+1)
    for (std::size_t i = 0; i < v.size() - 1; i++) { 
        if (v[i] <= x && v[i + 1] > x) { 
            return std::make_tuple(
                std::make_tuple(i, i + 1), 
                true
            ); 
        } 
    }
    return std::make_tuple(std::make_tuple(999, 999), false);
}


Result find_sequential_greater_a(const Vector& v, Vector::value_type x) {
    // ex a
    // same as given fn but using std::find_if

    std::size_t idx = 1;

    auto it = std::find_if(
        v.begin(), 
        v.end() - 1, 
        [&x, &idx, &v](double val) { return val <= x && x < v[idx++]; }
    );

    if (it != v.end() - 1) {
        return std::make_tuple(
            std::make_tuple(
                std::distance(v.begin(), it), 
                std::distance(v.begin(), it + 1)), 
            true
        );
    }

    return std::make_tuple(std::make_tuple(999, 999), false);
}


Result find_sequential_greater_b(const Vector& v, Vector::value_type x) {
    // ex b
    // same as given fn but using the O(log(n)) std::lower_bound, std::upper_bound
    // 
    // note: this will give the same result as find_sequential_greater_greater only for a SORTED vector.

    // 1st element smaller than x
    auto it1 = std::lower_bound(v.begin(), v.end(), x);

    // 1st element larger than x
    auto it2 = std::upper_bound(it1, v.end(), x);

    if (it1 != v.end() && it1 != v.begin() && it2 != v.end()) {

        if (!(x == *it1)) it1 -= 1; // if it1 == v.begin(): no smaller element in the array.

        return std::make_tuple(
            std::make_tuple(
                std::distance(v.begin(), it1), 
                std::distance(v.begin(), it2)), 
            true
        );
    }

    return std::make_tuple(std::make_tuple(999, 999), false);
}


Result find_sequential_greater_c(const Vector& v, double x) {
    // ex c
    // same as given fn but using the O(log(n)) std::equal_range
    //
    // note: this will give the same result as find_sequential_greater_greater only for a SORTED vector,
    //       and if there is an element for which v[i] == x.

    auto pair = std::equal_range(v.begin(), v.end(), x);

    if ((pair.first != v.begin() || x == *pair.first) && pair.first != v.end() && pair.second != v.end() && *pair.second > x) {
        if (x < *pair.first) pair.first -= 1;
        return std::make_tuple(
            std::make_tuple(
                std::distance(v.begin(), pair.first), 
                std::distance(v.begin(), pair.second)), 
            true
        );
    }

    return std::make_tuple(std::make_tuple(999, 999), false);
}


int main() {

    // test find_sequential_greater_X procedures
    Vector v(10);
    for (int i = 0; i < v.size(); i++) {
        v(i) = i;
    }
    
    // run a bunch of test values 
    std::vector<Vector::value_type> testValues{ 
        -1,  // too small
        4,   // exact match
        4.3, // somewhere in the middle
        7.3, // somewhere in the middle
        100  // too large
    };

    for (auto arg : testValues) {
        std::cout << "\nTesting Value: " << arg << "\n";
        std::cout << "find_sequential_greater_g: " << std::get<0>(std::get<0>(find_sequential_greater_g(v, arg))) << ", " << std::get<1>(std::get<0>(find_sequential_greater_g(v, arg))) << "\n";
        std::cout << "find_sequential_greater_a: " << std::get<0>(std::get<0>(find_sequential_greater_a(v, arg))) << ", " << std::get<1>(std::get<0>(find_sequential_greater_a(v, arg))) << "\n";
        std::cout << "find_sequential_greater_b: " << std::get<0>(std::get<0>(find_sequential_greater_b(v, arg))) << ", " << std::get<1>(std::get<0>(find_sequential_greater_b(v, arg))) << "\n";
        std::cout << "find_sequential_greater_c: " << std::get<0>(std::get<0>(find_sequential_greater_c(v, arg))) << ", " << std::get<1>(std::get<0>(find_sequential_greater_c(v, arg))) << "\n";
    }

    // test find_if_not
    //      same as find_if but stops when false is first found (rather than true)
    auto it = std::find_if_not(
        v.begin(),
        v.end(),
        [](double val) { return val <= 4.3; });

    if (it != v.end()) {
        std::cout << "First value not <= 4.3: " << *it << "\n";
    }

    return 0;
}