#ifndef RUNTIMEUTILS_HPP
#define RUNTIMEUTILS_HPP

#include <stdlib.h> // atof
#include <string.h> // strcmp
#include <iostream>
#include <vector>
#include "equations.hpp"
#include "utils.hpp"
#include "BaseSolver.hpp"
#include "FESolver.hpp"
#include "AdaptiveFESolver.hpp"
#include "RKSolver.hpp"
#include "AdaptiveRKSolver.hpp"
#include "ParallelIserNorSolver.hpp"


// Runtime checks
void check_minimum_parameters_number(const int argc);

// Initializations
void initialize_data(const int rank, char* test_number,
  EquationFunction* & fun_ptr, double & initial_time,
  double & final_time, Rnvector & initial_condition);
void initialize_solver(int argc, char* argv[], BaseSolver* & problem_ptr,
  double initial_step, double tolerance, const BaseEquation & equation);

#endif //RUNTIMEUTILS_HPP
