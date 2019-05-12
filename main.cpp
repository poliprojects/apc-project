#include<iostream>
#include "BaseSolver.hpp"
#include "BaseEquation.hpp"
#include "FESolver.hpp"
#include "utils.hpp"
#include "AdaptiveFESolver.hpp"
#include "RKSolver.hpp"


int main()
{
  //Initialization of test specific features
  #if defined TEST_1
    std::cout << std::endl << "Running Test 1" << std::endl << std::endl;
    double initial_time = 0;
    double final_time = 1;
    Rnvector initial_condition{0};
    double initial_step = 0.01;
    // Only for adaptive methods
    double tolerance = 1e-2;
    // Only for RK (RK2 = Heun)
    std::vector<std::vector<double>> a;
    std::vector<double> a1{ 0, 0 };
    std::vector<double> a2{ 1, 0 };
    a.push_back( a1 );
    a.push_back( a2 );
    std::vector<double> b{ 0.5, 0.5 };
    std::vector<double> c{ 0, 1 };
  #elif defined TEST_2
    std::cout << std::endl << "Running Test 2" << std::endl << std::endl;
    double initial_time = 0;
    double final_time = 30;
    Rnvector initial_condition{1};
    double initial_step = 0.5;
    // Only for adaptive methods
    double tolerance = 1e-2;
    // Only for RK (RK2 = Heun)
    std::vector<std::vector<double>> a;
    std::vector<double> a1{ 0, 0 };
    std::vector<double> a2{ 1, 0 };
    a.push_back( a1 );
    a.push_back( a2 );
    std::vector<double> b{ 0.5, 0.5 };
    std::vector<double> c{ 0, 1 };
  #elif defined TEST_3
    std::cout << std::endl << "Running Test 3" << std::endl << std::endl;
    double initial_time = -1;
    double final_time = 5;
    Rnvector initial_condition{1};
    double initial_step = 0.1;
    // Only for adaptive methods
    double tolerance = 1e-2;
    // Only for RK (RK2 = Heun)
    std::vector<std::vector<double>> a;
    std::vector<double> a1{ 0, 0 };
    std::vector<double> a2{ 1, 0 };
    a.push_back( a1 );
    a.push_back( a2 );
    std::vector<double> b{ 0.5, 0.5 };
    std::vector<double> c{ 0, 1 };
  #endif


  //Initialization of the solver
  //NB: the actual definition of fun depends on the test chosen (see utils.hpp)
  EquationFunction fun;
  BaseEquation equation(initial_time, final_time, fun, initial_condition);
  FESolver FEProblem(initial_step, equation);
  AdaptiveFESolver AdaptiveFEProblem(initial_step, equation, tolerance,
    initial_step / 10);
  RKSolver RKProblem(initial_step, equation, a, b, c);

  //Solves the problem
  FEProblem.solve();
  AdaptiveFEProblem.solve();
  RKProblem.solve();

  //Prints problem characteristics on screen
  FEProblem.print();
  AdaptiveFEProblem.print();
  RKProblem.print();

  #if defined TEST_1
    FEProblem.save_sol_to_file("solution_1.txt");
    AdaptiveFEProblem.save_sol_to_file("solution_1_adap.txt");
    RKProblem.save_sol_to_file("solution_1_RK.txt");
  #elif defined TEST_2
    FEProblem.save_sol_to_file("solution_2.txt");
    AdaptiveFEProblem.save_sol_to_file("solution_2_adap.txt");
    RKProblem.save_sol_to_file("solution_2_RK.txt");
  #elif defined TEST_3
    FEProblem.save_sol_to_file("solution_3.txt");
    AdaptiveFEProblem.save_sol_to_file("solution_3_adap.txt");
    RKProblem.save_sol_to_file("solution_3_RK.txt");
  #endif

  return 0;
}
