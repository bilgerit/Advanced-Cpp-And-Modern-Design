// Vector and Matrix Expressions
// 
// Herein we apply various operations to vectors and matrices:
//   vectors:
//      inner and outer prod, addition and subtration between two vectors
//      computing norms (euclidian, l1, max norm) of a vector
//   matrices:
//      computing norms (l1, max norm) of a matrix
//      product of a matrix and vector
// 
// Tobias Bilgeri, 31.1.2024

// ignore warnings related to deprecation of std::iterator templates used by boost
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

#include <iostream>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>

using namespace boost::numeric::ublas;

int main() {
    vector<double> v1(3);
    vector<double> v2(3);

    for (int i = 0; i < v1.size(); i++) {
        v1(i) = i;
        v2(i) = 2;
    }

    std::cout << "v1: " << v1 << "\n";
    std::cout << "v2: " << v2 << "\n";

    // inner prod
    double inner = inner_prod(v1, v2);
    std::cout << "inner product: " << inner << "\n";

    // outer prod
    matrix<double> outer = outer_prod(v1, v2);
    std::cout << "outer product: " << outer << "\n";

    // addition
    vector<double> sum = v1 + v2;
    std::cout << "sum: " << sum << "\n";

    // subtraction
    vector<double> diff = v1 - v2;
    std::cout << "difference: " << diff << "\n";

    // euclidian norm: vector
    double v1_norm_l2 = norm_2(v1);
    std::cout << "euclidean norm: " << v1_norm_l2 << "\n";

    // l1 norm: vector
    double v1_norm_l1 = norm_1(v1);
    std::cout << "L1 norm: " << v1_norm_l1 << "\n";

    // max norm: vector
    // norm_inf v = maximum (abs (v [i]))
    double v1_norm_max = norm_inf(v1);
    std::cout << "max norm: " << v1_norm_max << "\n";

    // matrix
    std::cout << "matrix: " << outer << "\n";

    // l1 norm: matrix
    double matrix_norm_l1 = norm_1(outer);
    std::cout << "Matrix L1 norm: " << matrix_norm_l1 << "\n";

    // max norm: matrix
    double matrix_norm_inf = norm_inf(outer);
    std::cout << "Matrix max norm: " << matrix_norm_inf << "\n";

    // product of (matrix, vector).
    vector<double> prod_res = prod(outer, v1);
    std::cout << "Product of matrix and vector: " << prod_res << "\n";
    
    return 0;
}