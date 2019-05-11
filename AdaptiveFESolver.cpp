#include "AdaptiveFESolver.hpp"


double AdaptiveFESolver::step(const double tbar, const Rnvector &ubar,
	const Rnvector &fubar) const
{
  
	double hn = h; // initialize adaptive step to starting step
	const std::size_t n = ubar.size();
	bool stop = false;

	// Adaptive loop
	while(hn / 2 >= hmin and !stop)
	{
		// Compute two solutions with different steps through FE method
		Rnvector uh = ubar + hn * fubar;
		Rnvector uh2 = ubar + (hn / 2) * fubar;

		// Compute error in infinity norm
		double error = std::max_element( abs(uh - uh2) );

		// Termination criterion
		(error < tol/2) ? (stop = true) : (hn = hn/2);
	}

	return hn/2;
}


void AdaptiveFESolver::solve()
{
  // Initialization of the time instants vector
  std::vector<double> times( Nh+1 );
  double tn = equation.get_tin();
  times[0] = tn;

  // Take solution at time 0 and function f from data
  Rnvector un = solution[0];
  EquationFunction f = equation.get_f();

  // Solution loop
  Rnvector un1( un.size() ); // solution at time n+1
  for( unsigned n = 0; n < Nh; n++ )
  {
    Rnvector f_eval = f( times[n], un );

    double hn = step(times[n], un, f_eval); // compute adaptive step
    un1 = un + h*f_eval;
    //for( std::size_t i = 0; i < un.size(); i++ )
    //  un1.push_back( un[i] + hn*f_eval[i] );

    solution.push_back( un1 );
    un = un1;
    un1.clear();
  }
}
