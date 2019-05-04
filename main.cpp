#include<iostream>
#include"BaseSolver.hpp"
#include"BaseEquation.hpp"
#include"utils.hpp"
#include"FESolver.hpp"

int main() {

  double final_time = 1;
  EquationFunction fun;
  Rnvector initial_condition(0);
  BaseEquation equation(final_time, fun, initial_condition);

  double initial_step = 0.1;
  FESolver problem(initial_step, equation);


  return 0;
}
