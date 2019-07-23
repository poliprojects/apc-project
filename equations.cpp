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
    std::vector<double> c1 = { 2, 0, 0, 0 };
    std::vector<double> c2 = { 0, 3, -2, 0 };
    std::vector<double> c3 = { 0, 0, 5, 0 };
    std::vector<double> c4 = { 0, 0, 0, 1 };
    std::vector<std::vector<double>> c = { c1, c2, c3, c4 };
    double d = 1;
    y[0] = ( c[0][0]*y_old[0] + c[0][1]*y_old[1]
           + c[0][2]*y_old[2] + c[0][3]*y_old[3] ) * sin(d*t) * exp(-t);
    y[1] = ( c[1][0]*y_old[0] + c[1][1]*y_old[1]
           + c[1][2]*y_old[2] + c[1][3]*y_old[3] ) * sin(d*t) * exp(-t);
    y[2] = ( c[2][0]*y_old[0] + c[2][1]*y_old[1]
           + c[2][2]*y_old[2] + c[2][3]*y_old[3] ) * sin(t) * exp(-t);
    y[3] = ( c[3][0]*y_old[0] + c[3][1]*y_old[1]
           + c[3][2]*y_old[2] + c[3][3]*y_old[3] ) * sin(t) * exp(-t);
    return y;
}
