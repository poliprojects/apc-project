#include "FESolver.hpp"


FESolver::FESolver(double step, const BaseEquation &eq):
	BaseSolver(step, eq)
{
	Nh = ( equation.get_tfin() - equation.get_tin() ) / h;
}

/// \param   tn   Present time instant
/// \param   un   Present value of the solution
/// \param   h    Step size
/// \return  un1  Solution at the following time instant
Rnvector FESolver::single_step(const double tn, const Rnvector &un,
	const double h) const
{
	EquationFunction &f = equation.get_f();
	Rnvector f_eval = f( tn, un );
	Rnvector un1 = un + h*f_eval;
	return un1;
}

void FESolver::solve()
{
	//Initialization of time instants
	times.resize( Nh+1 );
	double tn = equation.get_tin();
	for( std::size_t i = 0; i < Nh+1; i++ )
	{
		times[i] = tn;
		tn += h;
	}

	Rnvector un = solution[0]; // solution at n-th time, initialized at t=tin
	Rnvector un1( un.size() ); // solution at (n+1)-th time

	// Solution loop
	for( unsigned n = 0; n < Nh; n++ )
	{
		un1 = single_step( times[n], un, h );
		solution.push_back( un1 );
		un = un1;
		un1.clear();
	}
}

void FESolver::print_solver_spec() const
{
	std::cout << "Solved using: Forward Euler" << std::endl;
	std::cout << "h  = " << h << std::endl;
	std::cout << "Nh = " << Nh << std::endl;
	std::cout << std::endl;
}
