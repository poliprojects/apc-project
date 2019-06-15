#include "AdaptiveRKSolver.hpp"


void AdaptiveRKSolver::solve()
{
    // Initialization of the time instants vector
    times.push_back( equation.get_tin() );
    double tfin = equation.get_tfin();

    Rnvector un = solution[0]; // solution at n-th time, initialized at t=tin

    unsigned n = 0;
    double hn = h;
    double tn = times[0];

    while( tn+hn < tfin )
    {
        // Single iteration with step hn
        Rnvector uh1 = RKSolver::single_step( tn, un, hn );

        // Double iteration with step hn/2
        Rnvector utemp = RKSolver::single_step( tn, un, hn/2 );
        Rnvector uh2   = RKSolver::single_step( tn+hn/2, utemp, hn/2 );

        // Compute error in infinity norm
        Rnvector diff = abs( uh2 - uh1 );
        double error = *std::max_element( diff.cbegin(), diff.cend() ) /
            ( exp2( n_stages+1 ) - 1 );

        if( error < tol or hn < hmin ) // termination criteria
        {
            times.push_back( tn + hn );
            tn += hn;
            solution.push_back( uh2 );
            un = uh2;

            if( error < tol / exp2( n_stages+1 ) )
                hn *= 2;
            n++;
        }
        else
            hn = hn / 2;
    }

    // Last time instant is exactly equal to tfin
    hn = tfin - tn;
    if( hn != 0 )
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
    std::cout << "Tolerance  = " << tol  << std::endl;
    std::cout << std::endl;
}
