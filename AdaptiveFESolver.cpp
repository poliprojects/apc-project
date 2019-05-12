#include "AdaptiveFESolver.hpp"


double AdaptiveFESolver::step(const double tbar, const Rnvector &ubar,
	const Rnvector &fubar) const
{

	double hn = h; // initialize adaptive step to starting step
	bool stop = false;

	// Adaptive loop
	while(hn / 2 >= hmin and !stop)
	{
		// Compute two solutions with different steps through FE method
		Rnvector uh = ubar + hn * fubar;
		Rnvector uh2 = ubar + (hn / 2) * fubar;

		// Compute error in infinity norm
    Rnvector diff = abs(uh - uh2);
		double error = *std::max_element( diff.cbegin(), diff.cend() );

		if( error < tol/2 ) // termination criterion
    {
      stop = true;
      //std::cout << "tol\n"; //DEBUG
    }
    else
    {
      hn = hn/2;
      //std::cout << "half\n"; //DEBUG
    }
	}

	return hn/2;
}


void AdaptiveFESolver::solve()
{
  // Initialization of the time instants vector
  times.push_back( equation.get_tin() );
  double tfin = equation.get_tfin();

  // Take solution at time 0 and function f from data
  Rnvector un = solution[0];
  EquationFunction f = equation.get_f();

  // Solution loop
  Rnvector un1( un.size() ); // solution at time n+1
  unsigned n = 0;
  bool stop = false;

  while( !stop )
  {
    Rnvector f_eval = f( times[n], un );
    double hn = step(times[n], un, f_eval); // compute adaptive step

    if( times[n] + hn > tfin ) // out of range
      stop = true;
    else
    {
      times.push_back( times[n] + hn );
      un1 = un + hn*f_eval;
      solution.push_back( un1 );

      un = un1;
      un1.clear();
      n++;
    }

  }

  //for(auto &ti:times) std::cout << ti << " "; //DEBUG
}

void AdaptiveFESolver::print_solver_spec() const
{
	std::cout << "Solved using: Adaptive Forward Euler" << std::endl;
  std::cout << "Starting h = " << h    << std::endl;
  std::cout << "Minimum h  = " << hmin << std::endl;
  std::cout << "Tolerance  = " << tol  << std::endl;
	std::cout << std::endl;
}

void AdaptiveFESolver::save_sol_to_file(const std::string &file_name) const
{
  std::string times_file_name = "times_" + file_name;

  std::ofstream solution_stream{file_name};
  std::ofstream times_stream{times_file_name};
  if( !solution_stream or !times_stream )
  {
    std::cerr << "Cannot open an input file(s)." << std::endl;
    return;
  }
  //Save the computed solution
  for( auto un : solution )
  {
    for( auto val : un )
      solution_stream << val << " ";
    solution_stream << std::endl;
  }
  // Save time instants
  for( auto tn : times )
    times_stream << tn << "\n";
}
