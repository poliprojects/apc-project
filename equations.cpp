#include "equations.hpp"

// Examples of test equations
Rnvector EquationFunction_1::operator() ( const double &t, Rnvector y ) const
{
    return 5*y - 3;
}

Rnvector EquationFunction_2::operator() ( const double &t, Rnvector y ) const
{
    return (-1.0)*y;
}

Rnvector EquationFunction_3::operator() ( const double &t, Rnvector y ) const
{
    return (-1.0)*y + t;
}

Rnvector EquationFunction_4::operator() ( const double &t, Rnvector y ) const
{
    assert( y.size() == 2 );
    Rnvector y_old{y};
    y[0] = - 3*y_old[0] -   y_old[1] + sin(t);
    y[1] =     y_old[0] - 5*y_old[1] - 2;
    return y;
}
