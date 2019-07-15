#include "ParallelAdaptiveIserNorSolver.hpp"


ParallelAdaptiveIserNorSolver::ParallelAdaptiveIserNorSolver(
    double step, const BaseEquation &eq, double tolerance, double min_step ):
    ParallelIserNorSolver( step, eq ), tol( tolerance ), hmin( min_step )
{
    // Adaptive version of Parallel Iserles-Nørsett
    method_name = "Adaptive Parallel IserNor";
}


void ParallelAdaptiveIserNorSolver::solve()
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
        Rnvector uh1 = ParallelIserNorSolver::single_step( tn, un, hn );

        // Double iteration with step hn/2
        Rnvector utemp = ParallelIserNorSolver::single_step( tn, un, hn/2 );
        Rnvector uh2   = ParallelIserNorSolver::single_step( tn+hn/2, utemp,
            hn/2 );

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

            if( error < tol / exp2( n_stages+1 ) )
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
        Rnvector utemp = ParallelIserNorSolver::single_step( tn, un, hn/2 );
        Rnvector uh2   = ParallelIserNorSolver::single_step( tn+hn/2, utemp,
            hn/2 );
        solution.push_back( uh2 );
    }
}
