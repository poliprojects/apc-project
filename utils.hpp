#ifndef UTILS_HPP
#define UTILS_HPP

#include<vector>
#include<cmath>

typedef double real;
typedef std::vector<real> Rnvector;

struct EquationFunction{
  Rnvector operator() (const double & t, const Rnvector & x) const{
    return x;
  }
};

#endif
