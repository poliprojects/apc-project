#include"FESolver.hpp"

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
  Rnvector u_n = solution[0];
  EquationFunction f = equation.get_f();

  //Solution loop
  Rnvector u_n1; //solution at time n+1
  for( unsigned n = 0; n < Nh; n++ )
  {
    Rnvector f_eval = f( times[n], u_n );
    for( std::size_t i = 0; i < u_n.size(); i++ )
    {
      double hn = step();
      u_n1.push_back( u_n[i] + hn*f_eval[i] );
    }

    solution.push_back( u_n1 );
    u_n = u_n1;
    u_n1.clear();
  }
}
