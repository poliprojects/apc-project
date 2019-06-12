#include "includes.hpp"

using namespace std::chrono;

// Expected arguments:
// argv[1] = test number
// argv[2] = solver identification code
// argv[3] = initial step (default to 0.1)
// argv[4] = tolerance (default to 1e-2)
int main( int argc, char * argv[] )
{
    // MPI initialization
    MPI_Init( &argc, &argv );
    int rank, size;
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

    // Checks if there are enough parameters to start the execution
    check_minimum_parameters_number( argc );

    // =========================================================================
    // INITIALIZATION OF TEST DEPENDENT DATA
    // =========================================================================
    // NB: the actual definition of fun depends on the test chosen (see
    // equations.hpp and equations.cpp files)

    EquationFunction* fun_ptr = nullptr;
    double initial_time;
    double final_time;
    Rnvector initial_condition;

    // Setting data from runtime parameters
    initialize_data( rank, argv[1], fun_ptr, initial_time, final_time,
        initial_condition );

    // Equation initialization using test dependent data
    BaseEquation equation(initial_time, final_time, *fun_ptr,
        initial_condition);


    // =========================================================================
    // INITIALIZATION OF THE SOLVER
    // =========================================================================
    // NB: the actual definition of solver depends on the method chosen (see
    // RuntimeUtils.hpp and RuntimeUtils.cpp files)

    BaseSolver* problem_ptr = nullptr;
    double initial_step = 0.1; // Changes mid-solving only in adaptive methods
    double tolerance = 1e-2; // Used only in adaptive methods

    // Solver inizialization from runtime parameters
    initialize_solver( argc, argv, problem_ptr, initial_step, tolerance,
        equation );

    // Problem initialization using the chosen solver
    BaseSolver &problem = *problem_ptr;


    // =========================================================================
    // SOLUTION
    // =========================================================================

    // Chrono starts
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    // Solution
    problem.solve();

    // Chrono ends
    high_resolution_clock::time_point t2 = high_resolution_clock::now();


    // =========================================================================
    // POSTPROCESSING
    // =========================================================================

    if( rank == 0 )
    {
        // Compute duration of the solution process
        auto duration = duration_cast<microseconds>( t2 - t1 ).count();

        // Prints problem characteristics on screen
    	  problem.print();

        // Prints duration of the solution process
        std::cout << "Solution time: " << duration << " μs" << '\n' << std::endl;

      	// Saves solution to file_name
      	// NB: the name of the file depends on the arguments passed at runtime
      	std::string test_number = argv[1];
        std::string method_name = argv[2];
      	std::string file_name = "solution_"+test_number+"_"+method_name+".txt";
      	problem.save_sol_to_file( file_name );
        std::cout << "Saved solution to file: " << file_name << '\n' << '\n';
    }

    // Releases dynamically allocated resources
    delete fun_ptr;
    delete problem_ptr;

    // MPI finalization
    MPI_Finalize();

    return 0;
}
