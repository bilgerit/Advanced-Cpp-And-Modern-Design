// Dense Matrices 101
// 
// Boost-ublas also supports rank-2 tensors (matrices) natively, including
// special matrices such as zero matrices, identity matrices (both demonstrated
// here), triangular matrices, etc.
// Matrices can be dynamically or statically sized, and column-major or row-major.
// Regular matrices support item assignments and trivial arithmetic operations (+=, -=, etc.),
// and are trivially printable.
// 
// Tobias Bilgeri, 30.01.2024

// ignore warnings related to deprecation of std::iterator templates used by boost
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

int main() {

    // ex. a. Exemplary Matrices
    // Note: matrices are rank-2 by definition in boost-ublas.

    // Dynamically sized matrices (size specified as constructor args)
    // row_major (i.e., rows are contiguous in memory)
    boost::numeric::ublas::matrix<double> m1(3, 3);

    // column_major (w/ all values initialized to 1)
    boost::numeric::ublas::matrix<double, boost::numeric::ublas::column_major> m2(3, 3, 1);

    // Fixed-size matrix (size specified as template args)
    boost::numeric::ublas::bounded_matrix<double, 3, 3> m3;


    // ex. b. Element Access
    for (unsigned i = 0; i < m1.size1(); ++i) {
        for (unsigned j = 0; j < m1.size2(); ++j) {
            m1(i, j) = i + j;
        }
    }

    // matrices are trivially printable
    std::cout << "m1: " << m1 << "\n";



    // ex. c. Arithmetic operations

    // assignment
    m2 = m1;
    std::cout << "m2: " << m2 << "\n";

    // addition
    m1 += m2;
    std::cout << "m1 += m2: " << m1 << "\n";

    // subtraction
    m1 -= m2;
    std::cout << "m1 -= m2: " << m1 << "\n";



    // ex. d. Resizing 

    // increasing the size: the new entries are not initialized and may show arbitrary values.
    m1.resize(3, 4, true);
    std::cout << "Resized m1 (preserve=true): " << m1 << "\n";

    // preserve=false: now all matrix entries are uninitialized.
    m1.resize(2, 2, false);
    std::cout << "Resized m1 (preserve=false): " << m1 << "\n";

    // ex. e. Zero-Matrix and Identity Matrix

    // zero matrix
    // Note: a matrix with all entries equalling zero can also be created via m4(3, 3, 0).
    //       however, a 'true' zero_matrix object as below does not support changing values / 
    //       assignment operations. 
    boost::numeric::ublas::zero_matrix<double> m4(3, 3);
    std::cout << "Zero matrix m4: " << m4 << "\n";

    // identity matrix
    // requires only a single constructor argument, since num_rows = num_cols by default.
    boost::numeric::ublas::identity_matrix<double> m5(3);
    std::cout << "Identity matrix m5: " << m5 << "\n";

    return 0;
}