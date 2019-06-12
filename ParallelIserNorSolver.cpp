#include "ParallelIserNorSolver.hpp"


ParallelIserNorSolver::ParallelIserNorSolver(double step,
    const BaseEquation & eq): RKSolver(step, eq, "IserNor")
{
    // Parallel version of Iserles-Nørsett
    method_name = "Parallel IserNor";
}


/// \param   tn   Present time instant
/// \param   un   Present value of the solution
/// \param   h    Step size
/// \return       Solution at the following time instant
Rnvector ParallelIserNorSolver::single_step(const double tn, const Rnvector &un,
    const double h) const
{
    // high_resolution_clock::time_point t1 = high_resolution_clock::now();
    // high_resolution_clock::time_point t2 = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>( t2 - t1 ).count();

  	int rank, size;
  	MPI_Comm_rank( MPI_COMM_WORLD, &rank ); // 0 or 1
  	MPI_Comm_size( MPI_COMM_WORLD, &size ); // 2

    Rnvector un1 = un;
    unsigned system_dim = un.size();
    Rnvector empty( system_dim, 0 );
    std::vector<Rnvector> K{ empty, empty, empty, empty }; // vector of K_i
    EquationFunction &f = equation.get_f();

    unsigned local_n_stages = a.size() / size; // 2
    unsigned first_stage = 2*rank; // 0 in rank 0, 2 in rank 1

    // t1 = high_resolution_clock::now();
  	for( unsigned i = first_stage; i < first_stage+local_n_stages; i++ )
  	{
  	  	// Linear combination of the previous computed K_i
        Rnvector sum_aij_Kj( system_dim, 0 );
  	  	// starts at first stage also in rank 1 since A21 2x2 block is empty
        for( unsigned j = first_stage; j < i; j++ )
          sum_aij_Kj = sum_aij_Kj + a[i][j] * K[j];

    		// Computes the new K_i
    		K[i] = fixed_point( f, tn, un, sum_aij_Kj, i );
    		sum_aij_Kj = sum_aij_Kj + a[i][i] * K[i];
  	}
    // t2 = high_resolution_clock::now();
    // duration = duration_cast<microseconds>( t2 - t1 ).count();
    // if( rank == 0 )
    //   std::cout << "Fixed point 0: " << duration << " μs" << '\n' << std::endl;
    // if( rank == 1 )
    //   std::cout << "Fixed point 1: " << duration << " μs" << '\n' << std::endl;
    //
    // t1 = high_resolution_clock::now();
  	if( rank == 0 )
  	{
    		for( unsigned i = 0; i < 2; i++ )
    		{
    	  		// Send K[0], K[1]
      			MPI_Send( &K[i][0], system_dim, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD );
    		}
    		for( unsigned i = 2; i < 4; i++ )
    		{
	    	  	// Recieve K[2], K[3]
	      		MPI_Recv( &K[i][0], system_dim, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD,
	  		    	MPI_STATUS_IGNORE );
	    	}
  	}
  	else if( rank == 1 )
  	{
  	  	for( unsigned i = 0; i < 2; i++ )
  	  	{
  	  	  	// Recieve K[0], K[1]
  	    		MPI_Recv( &K[i][0], system_dim, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
  			    	MPI_STATUS_IGNORE );
  		  }
    		for( unsigned i = 2; i < 4; i++ )
    		{
      			// Send K[2], K[3]
  	    		MPI_Send( &K[i][0], system_dim, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD );
  	  	}
  	}
    // t2 = high_resolution_clock::now();
    // duration = duration_cast<microseconds>( t2 - t1 ).count();
    // if( rank == 0 )
    //   std::cout << "Communication 0: " << duration << " μs" << '\n' << '\n';
    // if( rank == 1 )
    //   std::cout << "Communication 1: " << duration << " μs" << '\n' << '\n';

    for( unsigned i = 0; i < n_stages; i++ )
        un1 = un1 + h * b[i] * K[i];

    return un1;
}
