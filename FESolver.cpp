#include "FESolver.hpp"

#include <cmath>


FESolver::FESolver( double step, const BaseEquation &eq ):
    BaseSolver( step, eq )
{
    Nh = static_cast<unsigned int>( ceil( ( equation.get_tfin()
        - equation.get_tin() ) / h ) );
}


/// \param   tn   Present time instant
/// \param   un   Present value of the solution
/// \param   hn    Step size
/// \return  un1  Solution at the following time instant
Rnvector FESolver::single_step( const double tn, const Rnvector &un,
    const double hn ) const
{
    EquationFunction &f = equation.get_f();
    Rnvector f_eval = f( tn, un );
    Rnvector un1 = un + hn*f_eval;
    return un1;
}


void FESolver::solve()
{
    //Initialization of time instants (except for the last one)
    times.resize( Nh+1 );
    double tn = equation.get_tin();
    for( std::size_t i = 0; i < Nh; i++ )
    {
        times[i] = tn;
        tn += h;
    }

    Rnvector un = solution[0]; // solution at n-th time, initialized at t=tin
    Rnvector un1( un.size() ); // solution at (n+1)-th time

    // Solution loop (except for the last step)
    for( unsigned n = 0; n < Nh-1; n++ )
    {
        un1 = single_step( times[n], un, h );
        solution.push_back( un1 );
        un = un1;
        un1.clear();
    }

    // Last step (to account for case where interval-step ratio is not integer)
    double tfin = equation.get_tfin();
    double hfin = tfin - times[Nh-1];
    times[Nh] = tfin;
    un1 = single_step( times[Nh-1], solution[Nh-1], hfin );
    solution.push_back( un1 );
}


void FESolver::print_solver_spec() const
{
    std::cout << "Solved using: Forward Euler" << std::endl;
    std::cout << "h  = " << h << std::endl;
    std::cout << "Nh = " << Nh << std::endl;
    std::cout << std::endl;
}
