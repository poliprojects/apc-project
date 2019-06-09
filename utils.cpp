#include "utils.hpp"


// Vector operators
Rnvector operator+( const Rnvector &x, const Rnvector &y ) // vector sum
{
	assert( x.size() == y.size() );
	Rnvector z( x.size() );
	for( std::size_t i = 0; i < x.size(); i++ )
		z[i] = x[i] + y[i];
	return z;
}

Rnvector operator*( const double lambda, const Rnvector &x ) // product by scalar
{
	Rnvector z( x.size() );
	for( std::size_t i = 0; i < x.size(); i++ )
		z[i] = lambda * x[i];
	return z;
}

Rnvector operator-( const Rnvector &x, const Rnvector &y ) // vector difference
{
	assert( x.size() == y.size() );
	return x + (-1.0)*y;
}

Rnvector operator+( const Rnvector &x, const double lambda ) // sum with scalar
{
	Rnvector y( x.size(), lambda );
	return x + y;
}

Rnvector operator-( const Rnvector &x, const double lambda ) // diff with scalar
{
	Rnvector y( x.size(), lambda );
	return x + (-1)*y;
}


Rnvector abs( const Rnvector &x ) // vector of absolute values
{
	Rnvector z( x.size() );
	for( std::size_t i = 0; i < x.size(); i++ )
		z[i] = std::abs( x[i] );
	return z;
}
