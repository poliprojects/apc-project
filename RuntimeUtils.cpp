#include "RuntimeUtils.hpp"


void check_minimum_parameters_number(const int argc)
{
	if( argc < 3 )
	{
		std::cerr <<
		"Missing mandatory parameters; at least test number and solver ID " <<
		"are required." << std::endl <<
		"Example: ./main 2 FE" << std::endl <<
		"For more information, please refer to the README file." << std::endl;
		exit(1);
	}
}


void initialize_data(const int rank, char* test_number,
  EquationFunction* & fun_ptr, double & initial_time,
  double & final_time, Rnvector & initial_condition)
{
	// Test 1
	if ( strcmp(test_number, "1") == 0 )
	{
    if( rank == 0 )
		  std::cout << std::endl << "Running Test 1" << std::endl << std::endl;
		fun_ptr = new EquationFunction_1;
		initial_time = 0;
		final_time = 1;
		initial_condition.push_back(0);
	}
  // Test 2
	else if ( strcmp(test_number, "2") == 0 )
	{
    if( rank == 0 )
		  std::cout << std::endl << "Running Test 2" << std::endl << std::endl;
		fun_ptr = new EquationFunction_2;
		initial_time = 0;
		final_time = 30;
		initial_condition.push_back(1);
	}
  // Test 3
	else if ( strcmp(test_number, "3") == 0  )
	{
    if( rank == 0 )
		  std::cout << std::endl << "Running Test 3" << std::endl << std::endl;
		fun_ptr = new EquationFunction_3;
		initial_time = -1;
		final_time = 5;
		initial_condition.push_back(1);
	}
  // Test 4
	else if ( strcmp(test_number, "4") == 0  )
	{
    if( rank == 0 )
		  std::cout << std::endl << "Running Test 4" << std::endl << std::endl;
		fun_ptr = new EquationFunction_4;
		initial_time = 0;
		final_time = 10;
		initial_condition.push_back(1);
		initial_condition.push_back(1);
	}
}


void initialize_solver(int argc, char* argv[], BaseSolver* & problem_ptr,
  double initial_step, double tolerance, const BaseEquation & equation)
{
  int size;
	MPI_Comm_size( MPI_COMM_WORLD, &size );

  // User defined initial step
  if ( argc > 3 )
    initial_step = atof( argv[3] );

  // User defined tolerance for adaptive methods
  if ( argc > 4 )
    tolerance = atof( argv[4] );

  // Parallel Iserles-Nørsett method
  if( size == 2 && strcmp(argv[2], "IserNor") == 0 )
  {
    problem_ptr = new ParallelIserNorSolver( initial_step, equation );
  }

  // Forward Euler method
	else if ( strcmp(argv[2], "FE") == 0 )
	{
		problem_ptr = new FESolver( initial_step, equation );
	}

  // Adaptive Forward Euler method
	else if ( strcmp(argv[2], "adapFE") == 0 )
	{
		problem_ptr = new AdaptiveFESolver( initial_step, equation,
			tolerance, tolerance );
	}

  // Runge Kutta method (user defined coefficients)
  else if ( strcmp(argv[2], "RK") == 0 )
  {
    // FE method
    std::vector<std::vector<double>> a;
    std::vector<double> a1{ 0 };
    a.push_back( a1 );
    std::vector<double> b{ 1 };
    std::vector<double> c{ 0 };
    problem_ptr = new RKSolver( initial_step, equation, a, b, c );
  }

  // Adaptive Runge Kutta method (user defined coefficients)
  else if ( strcmp(argv[2], "adapRK") == 0 )
  {
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
  else if ( strncmp(argv[2], "adap", 4) == 0 )
	{
    std::string name_prefix( argv[2] );
    std::string name_no_prefix = name_prefix.substr( 4, std::string::npos );
		problem_ptr = new AdaptiveRKSolver( initial_step, equation,
      name_no_prefix, tolerance, tolerance );
	}

  // Runge Kutta method (chosen among predefined ones)
  else
  {
    problem_ptr = new RKSolver( initial_step, equation, argv[2] );
  }
}
