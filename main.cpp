#include <iostream>
#include <math.h>
#include <string.h> // strcmp
#include <string>
#include <stdlib.h> // atof
#include <chrono>
#include "equations.hpp"
#include "BaseSolver.hpp"
#include "BaseEquation.hpp"
#include "FESolver.hpp"
#include "AdaptiveFESolver.hpp"
#include "RKSolver.hpp"
#include "AdaptiveRKSolver.hpp"

using namespace std::chrono;

// Expected arguments:
// argv[1] = test number
// argv[2] = solver identification code
// argv[3] = initial step (default to 0.1)
// argv[4] = tolerance (default to 1e-2)
int main( int argc, char * argv[] )
{
    // Check of minimum number of parameters required to execute the program
    if( argc < 3 )
    {
        std::cerr <<
        "Missing mandatory parameters; at least test number and solver ID " <<
        "are required." << std::endl <<
        "Example: ./main 2 FE" << std::endl <<
        "For more information, please refer to the README file." << std::endl;
        exit( 1 );
    }

    // =========================================================================
    // INITIALIZATION OF TEST DEPENDENT DATA
    // NB: the actual definition of fun depends on the test chosen (see
    // equations.hpp and equations.cpp files)
    // =========================================================================

    EquationFunction* fun_ptr = nullptr;
    double initial_time;
    double final_time;
    Rnvector initial_condition;

  // Test 1
    if ( strcmp( argv[1], "1" ) == 0 )
    {
        std::cout << std::endl << "Running Test 1" << std::endl << std::endl;
        fun_ptr = new EquationFunction_1;
        initial_time = 0;
        final_time = 1;
        initial_condition.push_back( 0 );
    }

  // Test 2
    else if ( strcmp( argv[1], "2" ) == 0 )
    {
        std::cout << std::endl << "Running Test 2" << std::endl << std::endl;
        fun_ptr = new EquationFunction_2;
        initial_time = 0;
        final_time = 30;
        initial_condition.push_back( 1 );
    }

  // Test 3
    else if ( strcmp( argv[1], "3" ) == 0  )
    {
        std::cout << std::endl << "Running Test 3" << std::endl << std::endl;
        fun_ptr = new EquationFunction_3;
        initial_time = -1;
        final_time = 5;
        initial_condition.push_back( 1 );
    }

  // Test 4
    else if ( strcmp( argv[1], "4" ) == 0  )
    {
        std::cout << std::endl << "Running Test 4" << std::endl << std::endl;
        fun_ptr = new EquationFunction_4;
        initial_time = 0;
        final_time = 10;
        initial_condition.push_back( 1 );
        initial_condition.push_back( 1 );
    }

    // Equation initialization using test dependent data
    BaseEquation equation( initial_time, final_time, *fun_ptr,
        initial_condition );


    // =========================================================================
    // INITIALIZATION OF THE SOLVER
    // =========================================================================

    BaseSolver* problem_ptr = nullptr;
    double initial_step = 0.1; // Changes mid-solving only in adaptive methods
    double tolerance = 1e-2; // Used only in adaptive methods

    // Forward Euler method
    if ( strcmp( argv[2], "FE" ) == 0 )
    {
        if ( argc > 3 )
            initial_step = atof( argv[3] );
        problem_ptr = new FESolver( initial_step, equation );
    }

    // Adaptive Forward Euler method
    else if ( strcmp( argv[2], "adapFE" ) == 0 )
    {
        if ( argc > 3 )
            initial_step = atof( argv[3] );
        if ( argc > 4 )
            tolerance = atof( argv[4] );
        problem_ptr = new AdaptiveFESolver( initial_step, equation,
            tolerance, tolerance );
    }

    // Runge Kutta method (user defined coefficients)
    else if ( strcmp( argv[2], "RK" ) == 0 )
    {
        if( argc > 3 )
        initial_step = atof( argv[3] );
        // FE method
        std::vector<std::vector<double>> a;
        std::vector<double> a1{ 0 };
        a.push_back( a1 );
        std::vector<double> b{ 1 };
        std::vector<double> c{ 0 };
        problem_ptr = new RKSolver( initial_step, equation, a, b, c );
    }

    // Adaptive Runge Kutta method (user defined coefficients)
    else if ( strcmp( argv[2], "adapRK" ) == 0 )
    {
        if( argc > 3 )
        initial_step = atof( argv[3] );
        // Heun method
        std::vector<std::vector<double>> a;
        std::vector<double> a1{ 0,  0 };
        std::vector<double> a2{ 1,  0 };
        a.push_back( a1 );
        a.push_back( a2 );
        std::vector<double> b{ 0.5, 0.5 };
        std::vector<double> c{   0,  1  };
        problem_ptr = new AdaptiveRKSolver( initial_step, equation, a, b, c,
        tolerance, tolerance );
    }

    // Adaptive Runge Kutta method (chosen among predefined ones)
    else if ( strncmp( argv[2], "adap", 4 ) == 0 )
    {
        if( argc > 3 )
            initial_step = atof( argv[3] );
    std::string name_prefix( argv[2] );
    std::string name_no_prefix = name_prefix.substr( 4, std::string::npos );
        problem_ptr = new AdaptiveRKSolver( initial_step, equation,
        name_no_prefix, tolerance, tolerance );
    }

    // Runge Kutta method (chosen among predefined ones)
    else
    {
        if ( argc > 3 )
            initial_step = atof( argv[3] );
        problem_ptr = new RKSolver( initial_step, equation, argv[2] );
    }


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

    // Compute duration of the solution process
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();

    // Prints problem characteristics on screen
    problem.print();

    // Prints duration of the solution process
    std::cout << "Solution time: " << duration << " ms" << std::endl <<
        std::endl;

    // Saves solution to file_name
    // NB: the name of the file depends on the arguments passed at runtime
    std::string test_number = argv[1];
    std::string method_name = argv[2];
    std::string file_name = "solution_"+test_number+"_"+method_name+".txt";
    problem.save_sol_to_file( file_name );

    // Releases dynamically allocated resources
    delete fun_ptr;
    delete problem_ptr;

    return 0;
}
