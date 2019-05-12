#include<iostream>
#include "BaseSolver.hpp"
#include "BaseEquation.hpp"
#include "FESolver.hpp"
#include "utils.hpp"
#include "AdaptiveFESolver.hpp"


int main()
{
  //Initialization of test specific features
  #if defined TEST_1
    std::cout << "Running Test 1" << std::endl;
    double initial_time = 0;
    double final_time = 1;
    Rnvector initial_condition{0};
    double initial_step = 0.01;
    double tolerance = 1e-2;
  #elif defined TEST_2
    std::cout << "Running Test 2" << std::endl;
    double initial_time = 0;
    double final_time = 30;
    Rnvector initial_condition{1};
    double initial_step = 0.5;
    double tolerance = 1e-2;
  #elif defined TEST_3
    std::cout << "Running Test 3" << std::endl;
    double initial_time = -1;
    double final_time = 5;
    Rnvector initial_condition{1};
    double initial_step = 0.2;
    double tolerance = 1e-1;
  #endif

  //Initialization of the solver
  //NB: the actual definition of fun depends on the test chosen (see utils.hpp)
  EquationFunction fun;
  BaseEquation equation(initial_time, final_time, fun, initial_condition);
  FESolver FEProblem(initial_step, equation);
  AdaptiveFESolver AdaptiveFEProblem(initial_step, equation, tolerance,
    initial_step / 20);

  //Solves the problem
  FEProblem.solve();
  AdaptiveFEProblem.solve();

  //Prints problem characteristics on screen
  FEProblem.print();
  AdaptiveFEProblem.print();

  #if defined TEST_1
    FEProblem.save_sol_to_file("solution_1.txt");
    AdaptiveFEProblem.save_sol_to_file("solution_1_adap.txt");
  #elif defined TEST_2
    FEProblem.save_sol_to_file("solution_2.txt");
    AdaptiveFEProblem.save_sol_to_file("solution_2_adap.txt");
  #elif defined TEST_3
    FEProblem.save_sol_to_file("solution_3.txt");
    AdaptiveFEProblem.save_sol_to_file("solution_3_adap.txt");
  #endif

  return 0;
}
