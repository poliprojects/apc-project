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
Rnvector operator-(const Rnvector &x, const Rnvector &y); // vector difference
Rnvector operator*(const double lambda, const Rnvector &x); // product by scalar
Rnvector abs(const Rnvector &x); // vector of absolute values


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
