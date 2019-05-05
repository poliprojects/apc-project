#include"BaseSolver.hpp"

BaseSolver::BaseSolver(double step, const BaseEquation & eq):
  h(step), equation(eq)
{
  //The solution at t=0 coincides with the initial condition
  solution.push_back(equation.get_x0());

  //Number of time steps, assuming h divides exactly tfin
  Nh = equation.get_tfin() / h;
}

void BaseSolver::print() const
{
  //Print the equation
  std::cout << "Equation:" << '\n';
  std::cout << "y'(t) = " << equation.get_f().f_string << "\t in [0," << equation.get_tfin() << "]" << '\n';
  std::cout << " y(0) = ";
  for( auto i : equation.get_x0() )
    std::cout << i << " ";
  std::cout << std::endl;

  //Print the solver specifications
  std::cout << "Discretization:" << '\n';
  std::cout << "h = " << h << '\n';
  std::cout << "Nh = " << Nh << '\n';
}

void BaseSolver::save_sol_to_file(const std::string & file_name) const
{
  std::ofstream output_stream{file_name};
  if(!output_stream)
  {
    std::cerr << "Can't open input file: \"" << file_name << "\"" << std::endl;
    return;
  }
  for( auto u_n : solution )
  {
    for( auto val : u_n )
      output_stream << val << " ";
    output_stream << std::endl;
  }

}