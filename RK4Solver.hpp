#ifndef RK4SOLVER_HPP
#define RK4SOLVER_HPP

#include "RKSolver.hpp"


class RK4Solver: public RKSolver
{
	public:
	// Constructors
	RK4Solver(double step, const BaseEquation &eq):
		RKSolver(
			step, eq,
			// matrix a
			{	{.0, .5, .0, .0},
				{.0, .0, .5, .0},
				{.0, .0, .0, 1.},
				{.0, .0, .0, .0} },
			// matrix b
			{.0, .5, .5, 1.},
			// matrix c
			{1/.6, 1/.3, 1/.3, 1/.6}
		) {}

	void print_solver_spec() const override;
};


#endif // RK4SOLVER_HPP
