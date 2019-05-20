#include "BaseSolver.hpp"


BaseSolver::BaseSolver(double step, const BaseEquation &eq):
  h(step), equation(eq)
{
  //The solution at t=0 coincides with the initial condition
  solution.push_back(equation.get_x0());
}

void BaseSolver::print() const
{
  //Print the equation
  std::cout << "Equation:" << std::endl;
  std::cout << equation.get_f().f_string << "\t in [" <<
    equation.get_tin() << "," << equation.get_tfin() << "]" << std::endl;
  std::cout << "y(" << equation.get_tin() << ") = ";
  for( auto i : equation.get_x0() )
    std::cout << i << " ";
  std::cout << std::endl;
  //Print the solver specifications
  print_solver_spec();
}

void BaseSolver::save_sol_to_file(const std::string & file_name) const
{
  std::ofstream output_stream{file_name};
  if(!output_stream)
  {
    std::cerr << "Cannot open input file: \"" << file_name << "\"" << std::endl;
    return;
  }
  //Save the computed solution
  output_stream << "Solution:" << std::endl;
  for( auto un : solution )
  {
    for( auto val : un )
      output_stream << val << " ";
    output_stream << std::endl;
  }
  // Save time instants
  output_stream << "Time instants:" << std::endl;
  for( auto tn : times )
    output_stream << tn << " ";
  output_stream << std::endl;
}
