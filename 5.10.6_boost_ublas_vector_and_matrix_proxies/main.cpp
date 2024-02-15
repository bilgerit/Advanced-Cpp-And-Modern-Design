// Vector and Matrix Proxies
// 
// Proxies used herein: matrix_row, matrix_column, matrix_range, matrix_slice
//      .... these are types natively provided in boost::numeric::ublas, together
//           with additional utility such as range(start, stop) for defining column 
//           and row spans, and slice(start, size, stride).
// 
// Tobias Bilgeri, 31.01.2024

// silence warning regarding boost using deprecated std::iterator
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>

// matrix proxies: matrix_row, etc.
#include <boost/numeric/ublas/matrix_proxy.hpp>

// printing tools (needed to use these types w/ stream operator <<)
#include <boost/numeric/ublas/io.hpp> 

int main() {
    using namespace boost::numeric::ublas;

    // exemplary matrix
    matrix<double> m(3, 3);
    for (unsigned i = 0; i < m.size1(); ++i) {
        for (unsigned j = 0; j < m.size2(); ++j) {
            m(i, j) = i * 3. + j;
        }
    }

    std::cout << "exemplary matrix: " << m << std::endl;

    // matrix_row 
    matrix_row<matrix<double>> mrow(m, 0);
    std::cout << "matrix_row object: " << mrow << std::endl;

    // matrix_column
    matrix_column mcol(m, 0);
    std::cout << "matrix_column: " << mcol << std::endl;

    // matrix_range (=submatrix)
    // initialized with the help of 'range'
    matrix_range mrange(m, range(0, 2), range(0, 2));
    std::cout << "matrix_range: " << mrange << std::endl;

    // matrix_slice
    // initialized with the help of 'slice' 
    // e.g. slice(0, 3, 4) defines [0, 4, 8]
    //      slice(0, 1, 3) defines [0, 3]
    matrix_slice mslice(m, slice(0, 1, 3), slice(0, 1, 3));
    std::cout << "matrix_slice: " << mslice << std::endl;

    return 0;
}