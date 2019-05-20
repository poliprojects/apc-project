#include "AdaptiveRKSolver.hpp"


void AdaptiveRKSolver::solve()
{
  // Initialization of the time instants vector
  times.push_back( equation.get_tin() );
  double tfin = equation.get_tfin();

  Rnvector un = solution[0]; // solution at n-th time, initialized at t=tin
  EquationFunction & f = equation.get_f();

  unsigned n = 0;
  double hn = h;
  double tn = times[0];

  while( tn+hn < tfin )
  {
    // RK algorithm below
    // // Single iteration with step hn
    // Rnvector uh1 = un + hn*f(tn, un);

    // // Double iteration with step hn/2
    // Rnvector utemp = un + (hn/2)*f(tn, un);
    // Rnvector uh2   = utemp + (hn/2)*f(tn + hn/2, utemp);

    // Compute error in infinity norm
    Rnvector diff = abs( uh2 - uh1 );
    double error = *std::max_element( diff.cbegin(), diff.cend() ) /
      ( pow(2,p+1) - 1 );

    if( error < tol/2 or hn < hmin ) // termination criteria
    {
      times.push_back( tn + hn );
      tn += hn;
      solution.push_back( uh2 );
      un = uh2;

      hn *= 2;
      n++;
    }
    else
    {
      hn = hn/2;
    }

  }

  // for(auto &ti:times) std::cout << ti << " "; //DEBUG
  // std::cout << std::endl; //DEBUG
}

void AdaptiveRKSolver::print_solver_spec() const
{
	std::cout << "Solved using: Adaptive Runge Kutta" << std::endl;
  std::cout << "Starting h = " << h    << std::endl;
  std::cout << "Minimum h  = " << hmin << std::endl;
  std::cout << "Tolerance  = " << tol  << std::endl;
	std::cout << std::endl;
}
