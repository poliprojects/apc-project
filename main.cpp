#include<iostream>
#include "BaseSolver.hpp"
#include "BaseEquation.hpp"
#include "FESolver.hpp"
#include "utils.hpp"

int main()
{
  //Initialization of test specific features
  #if defined TEST_1
    std::cout << "Running Test 1" << std::endl;
    double initial_time = 0;
    double final_time = 1;
    Rnvector initial_condition{0};
    double initial_step = 0.01;
  #elif defined TEST_2
    std::cout << "Running Test 2" << std::endl;
    double initial_time = 0;
    double final_time = 30;
    Rnvector initial_condition{1};
    double initial_step = 0.5;
  #elif defined TEST_3
    std::cout << "Running Test 3" << std::endl;
    double initial_time = -1;
    double final_time = 5;
    Rnvector initial_condition{1};
    double initial_step = 0.1;
  #endif

  //Initialization of the solver
  //NB: the actual definition of fun depends on the test chosen (see utils.hpp)
  EquationFunction fun;
  BaseEquation equation(initial_time, final_time, fun, initial_condition);
  FESolver problem(initial_step, equation);

  //Solves the problem
  problem.solve();

  //Prints problem characteristics on screen
  problem.print();

  #if defined TEST_1
    problem.save_sol_to_file("solution_1.txt");
  #elif defined TEST_2
    problem.save_sol_to_file("solution_2.txt");
  #elif defined TEST_3
    problem.save_sol_to_file("solution_3.txt");
  #endif

  return 0;
}
