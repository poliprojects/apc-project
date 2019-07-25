#include "equations.hpp"


// Examples of test equations

Rnvector EquationFunction_1::operator() ( const double &t, Rnvector y ) const
{
    return 5*y - 3 + 0*t;
}


Rnvector EquationFunction_2::operator() ( const double &t, Rnvector y ) const
{
    return (-1.0)*y + 0*t;
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


Rnvector EquationFunction_5::operator() ( const double &t, Rnvector y ) const
{
    return (-16.0)*y + 0*t;
}


Rnvector EquationFunction_6::operator() ( const double &t, Rnvector y ) const
{
        for( unsigned i = 0; i < y.size(); i++ )
            y[i] = exp2( -0.25*y[i] + 6 + 10*t );
        return y;
}


Rnvector EquationFunction_7::operator() ( const double &t, Rnvector y ) const
{
        for( unsigned i = 0; i < y.size(); i++ )
            y[i] = atan( 5 * ( 1 - t ) ) * y[i];
        return y;
}


Rnvector EquationFunction_8::operator() ( const double &t, Rnvector y ) const
{
    assert( y.size() == 4 );
    Rnvector y_old{y};
    y[0] = sin(2*3.1416/1000*t);
    y[1] = sin(2*3.1416/2000*t);
    y[2] = sin(2*3.1416/4000*t);
    y[3] = sin(2*3.1416/8000*t);
    return y;
}
