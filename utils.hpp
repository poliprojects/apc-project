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


// Vector operators
Rnvector operator+(const Rnvector &x, const Rnvector &y); // vector sum
Rnvector operator*(const double lambda, const Rnvector &x); // product by scalar
Rnvector operator-(const Rnvector &x, const Rnvector &y); // vector difference
Rnvector operator+(const Rnvector &x, const double lambda); // sum with scalar
Rnvector operator-(const Rnvector &x, const double lambda); // diff with scalar
Rnvector abs(const Rnvector &x); // vector of absolute values

#endif //UTILS_HPP
