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
Rnvector abs(const Rnvector &x); // vector of absolute values


struct EquationFunction
{
  EquationFunction(const std::string f_expr): f_string(f_expr) {}
  EquationFunction() = default;
  virtual ~EquationFunction() = default;
  virtual Rnvector operator()(const double & t, Rnvector y) const = 0;
  std::string f_string;
};

struct EquationFunction_1: public EquationFunction
{
  Rnvector operator()(const double & t, Rnvector y) const override;
  EquationFunction_1(): EquationFunction("y'(t) = 5*y(t) - 3") {}
};

struct EquationFunction_2: public EquationFunction
{
  Rnvector operator()(const double & t, Rnvector y) const override;
  EquationFunction_2(): EquationFunction("y'(t) = -y(t)") {}
};

struct EquationFunction_3: public EquationFunction
{
  Rnvector operator()(const double & t, Rnvector y) const override;
  EquationFunction_3(): EquationFunction("y'(t) = t - y(t)") {}
};

struct EquationFunction_4: public EquationFunction
{
  Rnvector operator()(const double & t, Rnvector y) const override;
  EquationFunction_4(): EquationFunction(
    "y1'(t) = -3*y1(t) -   y2(t) + sin(t)\ny2'(t) =    y1(t) - 5*y2(t) - 2\t")
  {} //TODO
};

// #if defined TEST_1
//   // struct EquationFunction
//   // {
//   //   Rnvector operator() (const double &t, Rnvector y) const {
//   //     for(auto &yi : y)
//   //       yi = 5*yi - 3;
//   //     return y;
//   //   }
//   //   //f(t,y(t)) to be printed on screen in the summary
//   //   std::string f_string = "5*y(t) - 3";
//   // };
//
// #elif defined TEST_2
//   struct EquationFunction
//   {
//     Rnvector operator() (const double &t, Rnvector y) const {
//       for(auto &yi : y)
//         yi = - yi;
//       return y;
//     }
//     //f(t,y(t)) to be printed on screen in the summary
//     std::string f_string = "-y(t)";
//   };
//
// #elif defined TEST_3
//   struct EquationFunction
//   {
//     Rnvector operator() (const double &t, Rnvector y) const {
//       for(auto &yi : y)
//         yi = t - yi;
//       return y;
//     }
//     //f(t,y(t)) to be printed on screen in the summary
//     std::string f_string = "t - y(t)";
//   };
// #endif

#endif //UTILS_HPP
