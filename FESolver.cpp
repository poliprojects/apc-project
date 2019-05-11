#include "FESolver.hpp"

double FESolver::step() const
{
  return h;
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

  //Take solution at time 0 and function f from data
  Rnvector un = solution[0];
  EquationFunction f = equation.get_f();

  //Solution loop
  Rnvector un1( un.size() ); //solution at time n+1
  for( unsigned n = 0; n < Nh; n++ )
  {
    Rnvector f_eval = f( times[n], un );
    un1 = un + h*f_eval;
    //for( std::size_t i = 0; i < un.size(); i++ )
    //  un1.push_back( un[i] + h*f_eval[i] );

    solution.push_back( un1 );
    un = un1;
    un1.clear();
  }
}
