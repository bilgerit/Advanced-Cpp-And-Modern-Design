// UBLAS dense vectors 101
// 
// UBLAS vectors are of similar to std::vector and can be resized during runtime via .resize().
// Furthermore, they allow for artithmetic operations via operators such as *=, +=, etc.
// Operations such as * only work with scalar+vector and not with two vectors in order to avoid
// ambiguities (inner prod, outer prod, or element wise?).
// They can also be trivially printed without helper function (via operator <<).
// They also support the usual begin and end iterators, and can therefore be trivially used with the
// std::algorithm procedures.
// 
// Tobias Bilgeri, 30.01.2024

// disable warning regarding std::iterator deprecation
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

#include <iostream>
#include <algorithm>
#include <functional>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

template<typename T> using UVector = boost::numeric::ublas::vector<T>;
template<typename T> using UScalarVector = boost::numeric::ublas::scalar_vector<T>;

int main() {

    UVector<double> v1(5, 1);

    for (unsigned i = 0; i < v1.size(); ++i) {
        std::cout << "v1 at index " << i << " using (i): " << v1(i) << "\n";
        std::cout << "v1 at index " << i << " using [i]: " << v1[i] << "\n";
    }

    UVector<double> v2(v1.size(), 2);
    for (unsigned i = 0; i < v2.size(); ++i) {
        std::cout << "v2 at index " << i << ": " << v2[i] << "\n";
    }

    v1 += v2;
    std::cout << "v1 += v2: " << v1 << "\n";

    v1 *= 2.5;
    std::cout << "v1 *= 2.5: " << v1 << "\n";

    // vector-vector multiplication is not supported
    // (probably due to ambiguity: outer prod, inner prod, or element wise?)
    // v1 *= v2;

    v1 -= v2;
    std::cout << "v1 -= v2: " << v1 << "\n";

    UVector<double> v3(5);
    std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::multiplies<double>());
    std::cout << "v3 = v1 * v2 (via std::tranform): " << v3 << "\n";

    // Element-wise multiplication is not supported
    // auto v4 = v1;
    // v4 *= v2;

    UScalarVector<double> v5(100, 5);
    std::cout << "v5: " << v5 << "\n";

    return 0;
}