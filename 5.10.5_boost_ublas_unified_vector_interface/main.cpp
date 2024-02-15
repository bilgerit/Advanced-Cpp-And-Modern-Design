// Unified Vector Interface for Generic Functions
// 
// In this exercise, we are given a generic print-function, which can print
// various containers satisfying a certain signature and supporing indexing 
// as well as begin and end iterators.
// 
// Following this example, we impelement a generic search function.
// 
// Tobias Bilgeri, 2024.01.31


// avoid error due to boost relying on a deprecated stl::iterators feature.
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING


#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <optional>
#include <boost/numeric/ublas/vector.hpp>


// given generic print fn:
template <typename T, 
          template <typename S, typename Alloc> class Container, 
          typename TAlloc> 
void print(const std::string& comment, const Container<T, TAlloc>& container) { 
    // A generic print function for general containers
    // prints the container twice: once using iterators, once using indexing.
    
    // print comment
    std::cout << comment << ": ";

    // We use lambda for readability 
    // a. iterators 
    auto f = [](const T& t) { std::cout << t << ", "; };

    std::for_each(container.begin(), container.end(), f); 
    std::cout << std::endl;

    // b. indexing 
    for (std::size_t i = 0; i < container.size(); ++i) { 
        std::cout << container[i] << ","; 
    } 
    std::cout << std::endl; 
}


// generic find function:
using SearchResult = std::pair<size_t, bool>;

template <typename T, 
          template <typename S, typename Alloc> class Container,
          typename TAlloc>
SearchResult find_value(const Container<T, TAlloc>& container, const T& value) {
    // A generic find function for general containers
    // note:
    //    I used the same templating as given in the print function.
    //    However, we could also simplify the templates by replacing
    //        <typename S, typename Alloc>
    //    with
    //        <typename, typename>
    //    since S and Alloc are not used anywhere, and the above line is enough to
    //    signal that the generic Container takes two template arguments.

    // find element within containers
    auto it = std::find(container.begin(), container.end(), value);

    // if found:
    if (it != container.end()) {
        return std::make_pair(std::distance(container.begin(), it), true);
    }
    else {
        return std::make_pair(-1, false);
    }
}


template<typename T>
void printSearchResult(const SearchResult& s, const T& value) {
    if (s.second) {
        std::cout << "Found value " << value << " at index " << s.first << "\n";
        return;
    }
    std::cout << "Value " << value << " not found.\n";
    return;
}


int main() {

    // stl vector
    std::vector<double> v1{ 2.0, 3.0, 4.0, -6.0 };
    print(std::string("STL Vector"), v1);
    printSearchResult(find_value(v1, 2.0), 2.0);
    printSearchResult(find_value(v1, 2.4), 2.4);
    printSearchResult(find_value(v1, -6.0), -6.0);

    // boost vector
    boost::numeric::ublas::vector<double> v2(4); 
    v2[0] = 2.0; 
    v2[1] = 3.0; 
    v2[2] = 4.0; 
    v2[3] = -6.0; 
    print(std::string("Boost Vector"), v2);
    printSearchResult(find_value(v2, 2.0), 2.0);
    printSearchResult(find_value(v2, 2.4), 2.4);
    printSearchResult(find_value(v2, -6.0), -6.0);

    return 0;
}