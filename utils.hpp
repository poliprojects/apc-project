#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <string>
#include <vector>


typedef std::vector<double> Rnvector;
// Solution: the first index is time, the second is the variable
typedef std::vector<Rnvector> SolutionType;


// Vector operators:
// vector sum
Rnvector operator+( const Rnvector &x, const Rnvector &y );
// product by scalar
Rnvector operator*( const double lambda, const Rnvector &x );
// vector difference
Rnvector operator-( const Rnvector &x, const Rnvector &y );
// sum with scalar (i.e. with constant vector)
Rnvector operator+( const Rnvector &x, const double lambda );
// difference with scalar (i.e. with constant vector)
Rnvector operator-( const Rnvector &x, const double lambda );
// vector of absolute values
Rnvector abs( const Rnvector &x );

#endif //UTILS_HPP
