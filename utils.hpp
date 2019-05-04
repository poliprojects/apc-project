// #include...
#include<cmath>

typedef double real;
typedef std::vector<real> Rnvector;

//! EquationFunction will be derived to exploit polymorphism
struct EquationFunction{
  virtual double operator() (const double & t, const Rnvector & x) const = 0;
}

//! Constant rhs
struct EquationFunction_1: public EquationFunction{
  double operator() (const double & t, const Rnvector & x) const override{
    return 1;
  }
}

//! Polynomial rhs in x
struct EquationFunction_2: public EquationFunction{
  double operator() (const double & t, const Rnvector & x) const override{
    return x + 1;
  }
}
