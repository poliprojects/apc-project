#ifndef UTILS_HPP
#define UTILS_HPP

#include<vector>
#include<string>
#include<cmath>


typedef double real;
typedef std::vector<real> Rnvector;
// Solution: the first index is time, the second is the variable
typedef std::vector<Rnvector> SolutionType;

// struct EquationFunction
// {
//   Rnvector operator() (const double & t, const Rnvector & y) const{
//     return y;
//   }
//   //f(t,y(t)) to be printed on screen in the summary
//   std::string f_string = "y(t)";
// };


#if defined TEST_1
  struct EquationFunction
  {
    Rnvector operator() (const double &t, Rnvector y) const {
      for( auto &y_i : y )
        y_i = 5*y_i - 3;
      return y;
    }
    //f(t,y(t)) to be printed on screen in the summary
    std::string f_string = "5*y(t) - 3";
  };

#elif defined TEST_2
  struct EquationFunction
  {
    Rnvector operator() (const double &t, Rnvector y) const {
      for( auto &y_i : y )
        y_i = - y_i;
      return y;
    }
    //f(t,y(t)) to be printed on screen in the summary
    std::string f_string = "-y(t)";
  };

#elif defined TEST_3
  struct EquationFunction
  {
    Rnvector operator() (const double &t, Rnvector y) const {
      for( auto &y_i : y )
        y_i = t - y_i;
      return y;
    }
    //f(t,y(t)) to be printed on screen in the summary
    std::string f_string = "t - y(t)";
  };
#endif

#endif //UTILS_HPP
