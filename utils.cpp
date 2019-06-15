#include "utils.hpp"


// Vector operators:
// Vector sum
Rnvector operator+( const Rnvector &x, const Rnvector &y )
{
    assert( x.size() == y.size() );
    Rnvector z( x.size() );
    for( std::size_t i = 0; i < x.size(); i++ )
        z[i] = x[i] + y[i];
    return z;
}


// Product by scalar
Rnvector operator*( const double lambda, const Rnvector &x )
{
    Rnvector z( x.size() );
    for( std::size_t i = 0; i < x.size(); i++ )
        z[i] = lambda * x[i];
    return z;
}


// Vector difference
Rnvector operator-( const Rnvector &x, const Rnvector &y ) 
{
    assert( x.size() == y.size() );
    return x + (-1.0)*y;
}


// Sum with scalar (i.e. with constant vector)
Rnvector operator+( const Rnvector &x, const double lambda ) 
{
    Rnvector y( x.size(), lambda );
    return x + y;
}


// Difference with scalar (i.e. with constant vector)
Rnvector operator-( const Rnvector &x, const double lambda )
{
    Rnvector y( x.size(), lambda );
    return x + (-1)*y;
}


// Vector of absolute values
Rnvector abs( const Rnvector &x )
{
    Rnvector z( x.size() );
    for( std::size_t i = 0; i < x.size(); i++ )
        z[i] = std::abs( x[i] );
    return z;
}
