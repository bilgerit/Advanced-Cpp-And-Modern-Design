// Sparce Matrices 101
// 
// Boost allows for easy usage of sparse matrices.
// Some strictly enforce this property: triangular matrices throw an error at runtime
//                                      when trying to assign to forbidden elements.
// Others allow easy assignment when need (see below: compressed_matrix).
// We can also create sparse views of non-sparce matrices via adapters.
// 
// 
// Tobias Bilgeri, 30.01.2024

// ignore warning caused by boost using a deprecated std feature 
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING 

#include <iostream>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>

// Shorthand-notation of some boost matrix types and tools.
using Complex = std::complex<double>;

template<typename T, typename L>
using Mat = boost::numeric::ublas::matrix<T, L>;

template<typename T> 
using SparseMat = boost::numeric::ublas::compressed_matrix<T>;

template<typename T, typename TRI, typename L> 
using TriangMat = boost::numeric::ublas::triangular_matrix<T, TRI, L>;

template<typename T, typename TRI>
using TriangAdaptor = boost::numeric::ublas::triangular_adaptor<T, TRI>;

// triangular mat specifiers
using Lower = boost::numeric::ublas::lower;
using Upper = boost::numeric::ublas::upper;

// matrix layout in memory
using RowMajor = boost::numeric::ublas::row_major;
using ColMajor = boost::numeric::ublas::column_major;


int main() {


    // ex. a. sparse matrix
    std::cout << "\n\nexercise a\n\n";

    SparseMat<Complex> m1(2, 2);

    // initialize some elements
    m1(0, 0) = Complex(1, 1);
    m1(1, 1) = Complex(2, 2);

    std::cout << "complex sparse matrix m1 w/ initialized diag elements: " << m1 << "\n";

    // erase some element
    m1.erase_element(1, 1);
    std::cout << "complex sparse matrix m1 after erasure of element (1, 1): " << m1 << "\n";

    // clearing
    m1.clear();
    std::cout << "complex sparse matrix m1 after calling .clear: " << m1 << "\n";



    // ex. b. triangular matrices (upper, lower, column-major, row-major)
    std::cout << "\n\nexercise b\n\n";

    // lower triang mat
    TriangMat<double, Lower, RowMajor> m2(2, 2);

    m2(0, 0) = 1.;
    m2(1, 0) = 2.;
    m2(1, 1) = 3.;
   
    // trying to elements outside of the lower triangle will lead to a runtime error:
    // m2(0, 1) = 1.;
    std::cout << "lower triangular matrix, row major: " << m2 << "\n";

    TriangMat<double, Upper, ColMajor> m3(2, 2);

    m3(0, 0) = 1.;
    m3(0, 1) = 2.;
    m3(1, 1) = 4.;
    std::cout << "upper triangular matrix, col major: " << m3 << "\n";



    // ex. c. triangular views of dense matrices
    std::cout << "\n\nexercise c\n\n";

    // dense matrix
    Mat<double, RowMajor> m4(2, 2, 1);
    std::cout << "dense matrix m4: " << m4 << "\n";

    // lower triangular view
    // triangular_adaptor allows creating a triangular view from a non-triangular matrix.
    TriangAdaptor<decltype(m4), Lower> m5(m4);
    std::cout << "lower triangular view of m4: " << m5 << "\n";

    TriangAdaptor<decltype(m4), Upper> m6(m4);
    std::cout << "upper triangular view of m4: " << m6 << "\n";

    return 0;
}