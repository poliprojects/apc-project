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


// Vector operations (component-wise)
//! Computes the sum of two vectors
Rnvector operator+( const Rnvector &x, const Rnvector &y );

//! Computes the product of a scalar and a vector
Rnvector operator*( const double lambda, const Rnvector &x );

//! Computes the difference of two vectors
Rnvector operator-( const Rnvector &x, const Rnvector &y );

//! Computes the sum of a vector with lambda times the unit vector
Rnvector operator+( const Rnvector &x, const double lambda );

//! Computes the difference of a vector with lambda times the unit vector
Rnvector operator-( const Rnvector &x, const double lambda );

//! Computes the absolute value of a vector
Rnvector abs( const Rnvector &x );


#endif //UTILS_HPP
