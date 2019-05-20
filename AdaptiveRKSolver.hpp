#ifndef ADAPTIVERKSOLVER_HPP
#define ADAPTIVERKSOLVER_HPP

#include "RKSolver.hpp"


class AdaptiveRKSolver: public RKSolver
{
	private:
		double tol;
		double hmin;
		// h is the starting value for the step and Nh has no meaning

	public:
		// Constructors
		AdaptiveRKSolver(double start_step, const BaseEquation &eq,
			double tolerance, double minimum_step):
			RKSolver(start_step, eq), tol(tolerance), hmin(minimum_step) {}
		AdaptiveRKSolver(double step, const BaseEquation &eq):
			AdaptiveRKSolver(step, eq, 1e-2, step/10) {} // keep?

		// Solving tool
		void solve();

		//Solution output
		void print_solver_spec() const override;
};

#endif // ADAPTIVERKSOLVER_HPP
