#include "AdaptiveRKSolver.hpp"


AdaptiveRKSolver::AdaptiveRKSolver( double start_step, const BaseEquation &eq,
    std::string name, double tolerance, double min_step, double max_step ):
    RKSolver( start_step, eq, name ), tol( tolerance ),
    hmin( min_step ), hmax( max_step )
    {
      // Makes hmax useless in case of explicit methods
      if( name != "IserNor" )
        hmax = std::numeric_limits<double>::infinity();
    }

void AdaptiveRKSolver::solve()
{
    // Initialization of the time instants vector
    double tin = equation.get_tin();
    double tfin = equation.get_tfin();
    times.push_back( tin );

    Rnvector un = solution[0]; // solution at n-th time, initialized at t=tin

    unsigned n = 0;
    double hn = h;
    double tn = times[0];

    while( 1 )
    {
        // Single iteration with step hn
        Rnvector uh1 = RKSolver::single_step( tn, un, hn );
        // Double iteration with step hn/2
        Rnvector utemp = RKSolver::single_step( tn, un, hn/2 );
        Rnvector uh2   = RKSolver::single_step( tn+hn/2, utemp, hn/2 );

        // Compute error in infinity norm
        Rnvector diff = abs( uh2 - uh1 );
        double error = *std::max_element( diff.cbegin(), diff.cend() ) /
            std::abs( *std::max_element( solution[n].cbegin(),
                solution[n].cend() ) );

        if( error < tol / 2 or hn < hmin ) // termination criteria
        {
            if( tn + hn > tfin ) // out of range: end cycle
                break;

            times.push_back( tn + hn );
            tn += hn;
            solution.push_back( uh2 );
            un = uh2;

            if( error < tol / exp2( n_stages+1 ) and 2*hn < hmax )
                hn *= 2;
            n++;
        }
        else
            hn = hn / 2;
    }

    // Last time instant is exactly equal to tfin
    hn = tfin - tn;
    if( hn > 1e-3 * ( tfin - tin ) ) // i.e. is nonzero: a last step is needed
    {
        times.push_back( tfin );
        Rnvector utemp = RKSolver::single_step( tn, un, hn/2 );
        Rnvector uh2   = RKSolver::single_step( tn+hn/2, utemp, hn/2 );
        solution.push_back( uh2 );
    }
}


void AdaptiveRKSolver::print_solver_spec() const
{
    std::cout << "Solved using: Adaptive Runge-Kutta (" << method_name << ")"
                        << std::endl;
    std::cout << "Starting h = " << h    << std::endl;
    std::cout << "Minimum h  = " << hmin << std::endl;
    if( method_name == "IserNor" )
      std::cout << "Maximum h = " << hmax << '\n';
    std::cout << "Tolerance  = " << tol  << std::endl;
    std::cout << std::endl;
}
