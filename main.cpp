#include <iostream>
#include <string.h> // strcmp
#include <string>
#include <stdlib.h> // atof
#include "BaseSolver.hpp"
#include "BaseEquation.hpp"
#include "FESolver.hpp"
#include "utils.hpp"
#include "AdaptiveFESolver.hpp"
#include "RKSolver.hpp"

// Expected arguments:
// argv[1] = test number
// argv[2] = solver identification code
// argv[3] = initial step (default to 0.1)
// argv[4] = tolerance (default to 1e-2)
int main( int argc, char * argv[] )
{
  // Initialization of test dependent data
  // NB: the actual definition of fun depends on the test chosen (see utils.hpp)
  EquationFunction* fun_ptr = nullptr;
  double initial_time;
  double final_time;
  Rnvector initial_condition;
  if ( strcmp(argv[1], "1") == 0 )
  {
    std::cout << std::endl << "Running Test 1" << std::endl << std::endl;
    fun_ptr = new EquationFunction_1;
    initial_time = 0;
    final_time = 1;
    initial_condition.push_back(0);
  }
  else if ( strcmp(argv[1], "2") == 0 )
  {
    std::cout << std::endl << "Running Test 2" << std::endl << std::endl;
    fun_ptr = new EquationFunction_2;
    initial_time = 0;
    final_time = 30;
    initial_condition.push_back(1);
  }
  else if ( strcmp(argv[1], "3") == 0  )
  {
    std::cout << std::endl << "Running Test 3" << std::endl << std::endl;
    fun_ptr = new EquationFunction_3;
    initial_time = -1;
    final_time = 5;
    initial_condition.push_back(1);
  }
  // Equation initialization using test dependent data
  BaseEquation equation( initial_time, final_time, *fun_ptr, initial_condition );

  // Initialization of the solver
  BaseSolver* problem_ptr = nullptr;
  double initial_step = 0.1; // Changes during solution only in adaptive methods
  double tolerance = 1e-2; // Used only in adaptive methods
  if ( strcmp(argv[2], "FE") == 0 )
  {
    if ( argc > 3 )
      initial_step = atof( argv[3] );
    problem_ptr = new FESolver( initial_step, equation );
  }
  else if ( strcmp(argv[2], "adapFE") == 0 )
  {
    if ( argc > 3 )
      initial_step = atof( argv[3] );
    if ( argc > 4 )
      tolerance = atof( argv[4] );
    problem_ptr = new AdaptiveFESolver( initial_step, equation,
                                        tolerance, tolerance );
  }
  else if ( strcmp(argv[2], "RK") == 0 )
  {
    if ( argc > 3 )
      initial_step = atof( argv[3] );
    // Heun method
    std::vector<std::vector<double>> a;
    std::vector<double> a1{ 0, 0 };
    std::vector<double> a2{ 1, 0 };
    a.push_back( a1 );
    a.push_back( a2 );
    std::vector<double> b{ 0.5, 0.5 };
    std::vector<double> c{ 0, 1 };
    problem_ptr = new RKSolver( initial_step, equation, a, b, c );
  }
  else if ( strcmp(argv[2], "adapRK") == 0 )
  {
      // ...
  }
  BaseSolver & problem = *problem_ptr;

  //Solves the problem
  problem.solve();

  //Prints problem characteristics on screen
  problem.print();

  // Save solution to file_name
  // NB: the name of the file depends on the arguments passed at runtime
  std::string test_number = argv[1];
  std::string method_name = argv[2];
  std::string file_name = "solution_" + test_number + "_" + method_name + ".txt";
  // std::cout << file_name << '\n';
  problem.save_sol_to_file( file_name );

  // Releasing dynamically allocated resources
  delete fun_ptr;
  delete problem_ptr;

  return 0;
}
