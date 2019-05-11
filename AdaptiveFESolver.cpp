#include "AdaptiveFESolver.hpp"

double AdaptiveFESolver::step(const double tbar, const Rnvector &ubar,
	const Rnvector &fubar) const
{
	// Starting step
	double h_n = h;

	const std::size_t n = ubar.size();
	bool stop = false;

	// Adaptive loop
	while(h_n / 2 >= hmin and !stop)
	{
		// Compute two solutions with different steps
		// for( std::size_t i = 0; i < n; i++ )
    	//{
    	//  u_h.push_back( ubar[i] + hn * fubar[i] );
    	//  u_h2.push_back( ubar[i] + (hn/2) * fubar[i] );
    	//}
		Rnvector u_h = ubar + h_n * fubar; // needs operator*
		Rnvector u_h2 = ubar + (h_n / 2) * fubar;

		// Compute error in infinity norm
		Rnvector diff = abs(u_h - u_h2);
		double error = std::max_element(diff);

		// Termination criterion
		if(error < tol/2)
			stop = true;
		else
			h_n = h_n/2;
	}
	return h_n/2;
}


void AdaptiveFESolver::solve()
{
  // Initialization of time instants
  std::vector<double> times( Nh+1 );

  double tn = equation.get_tin();
  for( std::size_t i = 0; i < Nh+1; i++ )
  {
    times[i] = tn;
    tn += h;
  }

  // Take solution at time 0 and function f from data
  Rnvector u_n = solution[0];
  EquationFunction f = equation.get_f();

  // Solution loop
  Rnvector u_n1; // solution at time n+1
  for( unsigned n = 0; n < Nh; n++ )
  {
    Rnvector f_eval = f( times[n], u_n );
    for( std::size_t i = 0; i < u_n.size(); i++ )
    {
      double h_n = step(times[n], u_n, f_eval);
      u_n1.push_back( u_n[i] + h_n*f_eval[i] );
    }

    solution.push_back( u_n1 );
    u_n = u_n1;
    u_n1.clear();
  }
}
