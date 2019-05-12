#include "FESolver.hpp"


FESolver::FESolver(double step, const BaseEquation &eq):
  BaseSolver(step, eq)
{
  Nh = ( equation.get_tfin() - equation.get_tin() ) / h;
}


void FESolver::solve()
{
  //Initialization of time instants
  std::vector<double> times( Nh+1 );
  double tn = equation.get_tin();
  for( std::size_t i = 0; i < Nh+1; i++ )
  {
    times[i] = tn;
    tn += h;
  }

  Rnvector un = solution[0]; // solution at n-th time, initialized at t=tin
  Rnvector un1( un.size() ); // solution at (n+1)-th time
  EquationFunction f = equation.get_f();

  // Solution loop
  for( unsigned n = 0; n < Nh; n++ )
  {
    Rnvector f_eval = f( times[n], un );
    un1 = un + h*f_eval;
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
  std::cout << std::endl;;
}
