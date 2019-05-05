#include<iostream>
#include"BaseSolver.hpp"
#include"BaseEquation.hpp"
#include"FESolver.hpp"
#include"utils.hpp"

int main()
{
  #if defined TEST_1
    std::cout << "Running Test 1" << '\n';
    double final_time = 1;
    EquationFunction fun;
    Rnvector initial_condition{0};
    BaseEquation equation(final_time, fun, initial_condition);
    double initial_step = 0.01;
    FESolver problem(initial_step, equation);

    problem.solve();
    problem.print();
    problem.save_sol_to_file("solution_1.txt");

  #elif defined TEST_2
    std::cout << "Running Test 2" << '\n';
    double final_time = 10;
    EquationFunction fun;
    Rnvector initial_condition{0};
    BaseEquation equation(final_time, fun, initial_condition);
    double initial_step = 0.1;
    FESolver problem(initial_step, equation);

    problem.solve();
    problem.print();
    problem.save_sol_to_file("solution_2.txt");

  #endif

  return 0;
}
