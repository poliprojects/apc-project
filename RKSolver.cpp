#include "RKSolver.hpp"

#include <cmath>


RKSolver::RKSolver( double step, const BaseEquation &eq,
    const std::vector<std::vector<double>> &a_,
    const std::vector<double> &b_,
    const std::vector<double> &c_ ):
    BaseSolver( step, eq ), a( a_ ), b( b_ ), c( c_ )
{
    // Check dimensions consintency
    assert( b.size() == c.size() && a.size() == a[0].size() &&
        b.size() == a.size() );
    // Set number of stages for every step
    n_stages = static_cast<unsigned int>( b.size() );
    // Set total number of steps (known a priori only in RK; has no meaning in
    // adaptive case)
    Nh = static_cast<unsigned int>( ceil ( ( equation.get_tfin()
        - equation.get_tin() ) / h ) );
    // User defined version of RK (to be printed on screen)
    method_name = "User defined";
}


RKSolver::RKSolver( double step, const BaseEquation &eq,
    const std::string name ): BaseSolver( step, eq )
{
    if( name == "Heun" )
    {
        a = { { 0,   0 },
            {   1,   0 } };
        b = { 0.5, 0.5 };
        c = {   0,   1 };
        // Set number of stages for every step
        n_stages = static_cast<unsigned int>( b.size() );
    }

    else if( name == "IserNor" )
    {
        a =
        {
            {1/3.,     0,         0,         0 },
            {1/3.,  1/3.,         0,         0 },
            {   0,     0,  0.594788,         0 },
            {   0,     0, -0.189576,  0.594788 }
        };
        b = { 1.978094,  1.978094, -1.478094, -1.478093 };
        c = {     1/3.,      2/3.,  0.594788,  0.405212 };
        // Set number of stages for every step
        n_stages = static_cast<unsigned int>( b.size() );
    }

    else if( name == "RK4" )
    {
        a =
        {
            {    0,    0,    0,    0 },
            {  0.5,    0,    0,    0 },
            {    0,  0.5,    0,    0 },
            {    0,    0,    1,    0 }
        };
        b = { 1/6., 1/3., 1/3., 1/6. };
        c = {    0,  0.5,  0.5,    1 };
        // Set number of stages for every step
        n_stages = static_cast<unsigned int>( b.size() );
    }

    else
    {
        std::cerr << "Unknown RK method. Aborting..." << std::endl << std::endl;
        exit( 1 );
    }

    // Set total number of steps (known a priori only in RK; has no meaning in
    // adaptive case)
    Nh = static_cast<unsigned int>( ( equation.get_tfin()
        - equation.get_tin() ) / h );
    // Set the proper version name of RK (to be printed on screen)
    method_name = name;
}


/// \param   tn   Present time instant
/// \param   un   Present value of the solution
/// \param   hn   Step size
/// \return       Solution at the following time instant
Rnvector RKSolver::single_step( const double tn, const Rnvector &un,
    const double hn ) const
{
    std::vector<Rnvector> K( n_stages ); // vector of K_i
    Rnvector un1 = un;
    EquationFunction &f = equation.get_f();

    for( unsigned i = 0; i < n_stages; i++ ) // for every row
    {
        // Linear combination of the previous computed K_i
        Rnvector sum_aij_Kj( equation.get_dimension(), 0 );
        for( unsigned j = 0; j < i; j++ )
            sum_aij_Kj = sum_aij_Kj + a[i][j] * K[j];

        // K_i is defined implicitly ( A[i][i] != 0 )
        if( is_implicit( i ) )
        {
            K[i] = fixed_point( f, tn, un, hn, sum_aij_Kj, i );
            sum_aij_Kj = sum_aij_Kj + a[i][i] * K[i];
        }

        // K_i can be computed explicitly ( A[i][i] == 0 )
        else
            K[i] = f( tn + c[i] * hn, un + hn * sum_aij_Kj );
    }

    for( unsigned i = 0; i < n_stages; i++ )
        un1 = un1 + hn * b[i] * K[i];

    return un1;
}


/// \param   f           Right-hand side
/// \param   tn          Present time instant
/// \param   un          Present value of the solution
/// \param   h_local     Step
/// \param   sum_aij_Kj  Linear combination of explicit (already available) Ks
/// \param   i           Index of the K to be computed by fixed point
/// \return              K computed by fixed point
Rnvector RKSolver::fixed_point( const EquationFunction &f, const double tn,
    const Rnvector &un, const double h_local, const Rnvector &sum_aij_Kj,
    const size_t i ) const
{
    unsigned n_iter = 0;
    unsigned Max_iter = 10000;

    Rnvector K0 = un;
    Rnvector K1 = f( tn + c[i] * h_local,
        un + h_local * sum_aij_Kj + h_local * a[i][i] * K0 );
    double error = compute_error( K0, K1 );
    K0 = K1;

    while( error > fixed_point_tol && n_iter < Max_iter )
    {
        K1 = f( tn + c[i] * h_local,
            un + h_local * sum_aij_Kj + h_local * a[i][i] * K0 );
        error = compute_error( K0, K1 );
        K0 = K1;
        n_iter++;
    }

    if( n_iter == Max_iter )
    {
        std::cerr << "Fixed point algorithm cannot converge. Try with a "
            << "smaller step size and/or decrease hmax." << std::endl
            << "Aborting..." << std::endl;
        exit(1);
    }

    return K0;
}

/// \param   K0     Previous value of K_i
/// \param   K0     Present value of K_i
/// \return         Fixed point error computed as | x - f(x) |
double RKSolver::compute_error( const Rnvector &K0, const Rnvector &K1 ) const
{
    double error = 0;
    for( size_t k = 0; k < K0.size(); k++ ) // k = dimension of the system
        error += std::abs( K0[k] - K1[k] );
    return error;
}


/// \param   K_index   Row index of A
/// \return  implicit  True if implicit, false otherwise
bool RKSolver::is_implicit( const size_t K_index ) const
{
    return ( a[K_index][K_index] != 0 );
}


void RKSolver::solve()
{
    // Initialization of time instants (except for the last one)
    times.resize( Nh+1 );
    double tn = equation.get_tin();
    for( std::size_t i = 0; i < Nh; i++ )
    {
        times[i] = tn;
        tn += h;
    }

    // Take solution at time 0 and function f from data
    Rnvector un = solution[0];

    // Solution loop (except for the last step)
    Rnvector un1( un.size() ); // solution at time n+1
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


void RKSolver::print_solver_spec() const
{
    std::cout << "Solved using: Runge-Kutta (" << method_name << ")"
        << std::endl;
    std::cout << "h  = " << h << std::endl;
    std::cout << "Nh = " << Nh << std::endl;
    std::cout << std::endl;
}
