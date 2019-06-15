#include "equations.hpp"


// Examples of test equations

Rnvector EquationFunction_1::operator() ( const double &t, Rnvector y ) const
{
    return 5*y - 3;
}


Rnvector EquationFunction_2::operator() ( const double &t, Rnvector y ) const
{
    return (-1.0)*y;  // Originale (TODO?)
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


// TODO
Rnvector EquationFunction_5::operator() ( const double &t, Rnvector y ) const
{
    return (-16.8)*y; // Tante iterazioni di punto fisso ma sbilanciate
}


Rnvector EquationFunction_6::operator() ( const double &t, Rnvector y ) const
{
      // Iterazioni punto fisso bilanciate (IserNor parallelo più efficiente)
        for( unsigned i = 0; i < y.size(); i++ )
            y[i] = exp2( -0.25*y[i] + 6 + 10*t );
        return y;
}
