#include "RKSolver.hpp"


RKSolver::RKSolver(double step, const BaseEquation & eq,
	const std::vector<std::vector<double>> & a_,
	const std::vector<double> & b_,
	const std::vector<double> & c_):
	BaseSolver(step, eq), a(a_), b(b_), c(c_)
{
	// Check dimensions consintency
	assert( b.size() == c.size() && a.size() == a[0].size() );
	// Set number of stages for every step
	n_stages = b.size();
	// Set total number of steps (known a priori only in RK; has no meaning in
	// adaptive case)
	Nh = ( equation.get_tfin() - equation.get_tin() ) / h;
}

/// \param   tn   Present time instant
/// \param   un   Present value of the solution
/// \param   h    Step size
/// \return  un1  Solution at the following time instant
Rnvector RKSolver::single_step(const double tn, const Rnvector &un,
	const double h) const
{
	std::vector<Rnvector> K( n_stages ); // vector of K_i
	Rnvector un1 = un;
	EquationFunction &f = equation.get_f();
	K[0] = f( tn, un );
	un1 = un1 + h * b[0] * K[0];

	for( unsigned i = 1; i < n_stages; i++ )
	{
		Rnvector sum_aij_Kj( equation.get_dimension(), 0 );
		for( unsigned j = 0; j < i; j++ )
			sum_aij_Kj = sum_aij_Kj + a[i][j] * K[j];
		K[i] = f( tn + c[i] * h, un + h * sum_aij_Kj );
		un1 = un1 + h * b[i] * K[i];
	}

	return un1;
}

void RKSolver::solve()
{
	//Initialization of time instants
	times.resize( Nh+1 );
	double tn = equation.get_tin();
	for( std::size_t i = 0; i < Nh+1; i++ )
	{
		times[i] = tn;
		tn += h;
	}
	
	//Take solution at time 0 and function f from data
	Rnvector un = solution[0];
	
	//Solution loop
	Rnvector un1( un.size() ); // solution at time n+1
	for( unsigned n = 0; n < Nh; n++ )
	{
		un1 = single_step( times[n], un, h );
		solution.push_back( un1 );
		un = un1;
		un1.clear();
	}
}

void RKSolver::print_solver_spec() const
{
	std::cout << "Solved using: Runge Kutta" << std::endl;
	std::cout << "h  = " << h << std::endl;
	std::cout << "Nh = " << Nh << std::endl;
	std::cout << std::endl;;
}
