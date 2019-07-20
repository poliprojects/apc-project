#ifndef RUNTIMEUTILS_HPP
#define RUNTIMEUTILS_HPP

#include "includes.hpp"

using namespace std::chrono;


// Runtime checks
void check_input_parameters( const int argc, char * argv[] );


// Initializations
void initialize_data( const int rank, char* test_number,
    EquationFunction* &fun_ptr, double &initial_time,
    double &final_time, Rnvector &initial_condition );
void initialize_solver( int argc, char* argv[], BaseSolver* &problem_ptr,
    double initial_step, double tolerance, double min_step, double max_step,
    const BaseEquation &equation );


#endif //RUNTIMEUTILS_HPP
