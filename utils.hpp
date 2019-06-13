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
// Vector sum
Rnvector operator+( const Rnvector &x, const Rnvector &y );
// Product by scalar
Rnvector operator*( const double lambda, const Rnvector &x );
// Vector difference
Rnvector operator-( const Rnvector &x, const Rnvector &y );
// Sum with scalar (i.e. with constant vector)
Rnvector operator+( const Rnvector &x, const double lambda );
// Difference with scalar (i.e. with constant vector)
Rnvector operator-( const Rnvector &x, const double lambda );
// Vector of absolute values
Rnvector abs( const Rnvector &x );

#endif //UTILS_HPP
