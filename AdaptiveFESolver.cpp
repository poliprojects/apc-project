#include "AdaptiveFESolver.hpp"


void AdaptiveFESolver::solve()
{
    // Initialization of the time instants vector
    times.push_back( equation.get_tin() );
    double tfin = equation.get_tfin();

    Rnvector un = solution[0]; // solution at n-th time, initialized at t=tin

    unsigned n = 0;
    double hn = h;
    double tn = times[0];

    while( 1 )
    {
        // Single iteration with step hn
        Rnvector uh1 = FESolver::single_step( tn, un, hn );

        // Double iteration with step hn/2
        Rnvector utemp = FESolver::single_step( tn, un, hn/2 );
        Rnvector uh2   = FESolver::single_step( tn+hn/2, utemp, hn/2 );

        // Compute error in infinity norm
        Rnvector diff = abs( uh2 - uh1 );
        double error = *std::max_element( diff.cbegin(), diff.cend() );

        if( error < tol/2 or hn < hmin ) // termination criteria
        {
            if( tn + hn > tfin ) // out of range: end cycle
                break;
            
            times.push_back( tn + hn );
            tn += hn;
            solution.push_back( uh2 );
            un = uh2;

            hn *= 2;
            n++;
        }
        else
            hn = hn / 2;
    }

    // Last time instant is exactly equal to tfin
    hn = tfin - tn;
    if( hn > 1e-5 ) // i.e. is nonzero: a last step is needed
    {
        times.push_back( tfin );
        Rnvector utemp = FESolver::single_step( tn, un, hn/2 );
        Rnvector uh2   = FESolver::single_step( tn+hn/2, utemp, hn/2 );
        solution.push_back( uh2 );
    }
}


void AdaptiveFESolver::print_solver_spec() const
{
    std::cout << "Solved using: Adaptive Forward Euler" << std::endl;
    std::cout << "Starting h = " << h    << std::endl;
    std::cout << "Minimum h  = " << hmin << std::endl;
    std::cout << "Tolerance  = " << tol  << std::endl;
    std::cout << std::endl;
}
