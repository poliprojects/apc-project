#include "utils.hpp"


Rnvector EquationFunction_1::operator() (const double &t, Rnvector y) const
{
  for(auto &yi : y)
    yi = 5*yi - 3;
  return y;
}

Rnvector EquationFunction_2::operator() (const double &t, Rnvector y) const
{
  for(auto &yi : y)
    yi = - yi;
  return y;
}

Rnvector EquationFunction_3::operator() (const double &t, Rnvector y) const
{
  for(auto &yi : y)
    yi = t - yi;
  return y;
}

// Vector operators
Rnvector operator+(const Rnvector &x, const Rnvector &y) // vector sum
{
  assert( x.size() == y.size() );
  Rnvector z( x.size() );
  for(std::size_t i = 0; i < x.size(); i++)
    z[i] = x[i] + y[i];
  return z;
}

Rnvector operator-(const Rnvector &x, const Rnvector &y) // vector difference
{
  assert( x.size() == y.size() );
  Rnvector z( x.size() );
  for(std::size_t i = 0; i < x.size(); i++)
    z[i] = x[i] - y[i];
  return z;
}

Rnvector operator*(const double lambda, const Rnvector &x) // product by scalar
{
  Rnvector z( x.size() );
  for(std::size_t i = 0; i < x.size(); i++)
    z[i] = lambda * x[i];
  return z;
}

Rnvector abs(const Rnvector &x) // vector of absolute values
{
  Rnvector z( x.size() );
  for(std::size_t i = 0; i < x.size(); i++)
    z[i] = std::abs(x[i]);
  return z;
}
