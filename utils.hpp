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


// VECTOR OPERATORS
// Vector sum:
inline Rnvector operator+(const Rnvector &x, const Rnvector &y)
{
  assert( x.size() == y.size() );
  Rnvector z( x.size() );
  for(std::size_t i = 0; i < x.size(); i++)
    z[i] = x[i] + y[i];
  return z;
}

// Vector difference:
inline Rnvector operator-(const Rnvector &x, const Rnvector &y)
{
  assert( x.size() == y.size() );
  Rnvector z( x.size() );
  for(std::size_t i = 0; i < x.size(); i++)
    z[i] = x[i] - y[i];
  return z;
}

// Product by scalar:
inline Rnvector operator*(const double lambda, const Rnvector &x)
{
  Rnvector z( x.size() );
  for(std::size_t i = 0; i < x.size(); i++)
    z[i] = lambda * x[i];
  return z;
}

// Vector of absolute values:
inline Rnvector abs(const Rnvector &x)
{
  Rnvector z( x.size() );
  for(std::size_t i = 0; i < x.size(); i++)
    z[i] = std::abs(x[i]);
  return z;
}


#if defined TEST_1
  struct EquationFunction
  {
    Rnvector operator() (const double &t, Rnvector y) const {
      for(auto &yi : y)
        yi = 5*yi - 3;
      return y;
    }
    //f(t,y(t)) to be printed on screen in the summary
    std::string f_string = "5*y(t) - 3";
  };

#elif defined TEST_2
  struct EquationFunction
  {
    Rnvector operator() (const double &t, Rnvector y) const {
      for(auto &yi : y)
        yi = - yi;
      return y;
    }
    //f(t,y(t)) to be printed on screen in the summary
    std::string f_string = "-y(t)";
  };

#elif defined TEST_3
  struct EquationFunction
  {
    Rnvector operator() (const double &t, Rnvector y) const {
      for(auto &yi : y)
        yi = t - yi;
      return y;
    }
    //f(t,y(t)) to be printed on screen in the summary
    std::string f_string = "t - y(t)";
  };
#endif

#endif //UTILS_HPP
