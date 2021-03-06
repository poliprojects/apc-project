#include "ParallelIserNorSolver.hpp"


ParallelIserNorSolver::ParallelIserNorSolver( double step,
    const BaseEquation &eq ): RKSolver( step, eq, "IserNor" )
{
    // Parallel version of Iserles-Nørsett
    method_name = "Parallel IserNor";
}


/// \param   tn   Present time instant
/// \param   un   Present value of the solution
/// \param   hn   Step size
/// \return       Solution at the following time instant
Rnvector ParallelIserNorSolver::single_step( const double tn,
    const Rnvector &un, const double hn ) const
{
    int rank, size;
    MPI_Comm_rank( MPI_COMM_WORLD, &rank ); // 0 or 1
    MPI_Comm_size( MPI_COMM_WORLD, &size ); // 2

    Rnvector un1 = un;
    int system_dim = static_cast<int>( un.size() );
    Rnvector empty( static_cast<std::size_t>( system_dim ), 0 );
    std::vector<Rnvector> K{ empty, empty, empty, empty }; // vector of K_i
    EquationFunction &f = equation.get_f();

    unsigned local_n_stages = static_cast<unsigned int>(
        static_cast<unsigned int>( a.size() ) /
        static_cast<unsigned int>( size ) ); // 2
    unsigned first_stage = static_cast<unsigned int>( 2*rank ); // 0 or 2

    for( unsigned i = first_stage; i < first_stage+local_n_stages; i++ )
    {
        // Linear combination of the previous computed K_i
        Rnvector sum_aij_Kj( static_cast<std::size_t>( system_dim ), 0 );
        // Starts at first stage also in rank 1 since A21 2x2 block is empty
        for( unsigned j = first_stage; j < i; j++ )
            sum_aij_Kj = sum_aij_Kj + a[i][j] * K[j];

        // Computes the new K_i
        K[i] = fixed_point( f, tn, un, hn, sum_aij_Kj, i );
        sum_aij_Kj = sum_aij_Kj + a[i][i] * K[i];
    }

    if( rank == 0 )
    {
        for( unsigned i = 0; i < 2; i++ )
        {
            // Send K[0], K[1]
            MPI_Send( &K[i][0], system_dim, MPI_DOUBLE, 1, 0,
                MPI_COMM_WORLD );
        }
        for( unsigned i = 2; i < 4; i++ )
        {
            // Receive K[2], K[3]
            MPI_Recv( &K[i][0], system_dim, MPI_DOUBLE, 1, 0,
                MPI_COMM_WORLD, MPI_STATUS_IGNORE );
        }
    }

    else if( rank == 1 )
    {
        for( unsigned i = 0; i < 2; i++ )
        {
            // Receive K[0], K[1]
            MPI_Recv( &K[i][0], system_dim, MPI_DOUBLE, 0, 0,
                MPI_COMM_WORLD, MPI_STATUS_IGNORE );
        }
        for( unsigned i = 2; i < 4; i++ )
        {
            // Send K[2], K[3]
            MPI_Send( &K[i][0], system_dim, MPI_DOUBLE, 0, 0,
                MPI_COMM_WORLD );
        }
    }

    for( unsigned i = 0; i < n_stages; i++ )
        un1 = un1 + hn * b[i] * K[i];

    return un1;
}
