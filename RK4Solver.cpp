#include "RK4Solver.hpp"

void RK4Solver::print_solver_spec() const
{
	std::cout << "Solved using: RK4" << std::endl;
	std::cout << "h  = " << h << std::endl;
	std::cout << "Nh = " << Nh << std::endl;
	std::cout << std::endl;
}
