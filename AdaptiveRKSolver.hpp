#ifndef ADAPTIVERKSOLVER_HPP
#define ADAPTIVERKSOLVER_HPP

#include "RKSolver.hpp"


class AdaptiveRKSolver: public RKSolver
{
	private:
		double tol;
		double hmin;
		// h is the starting value for the step and Nh has no meaning

	// TODO Note: a single_step() specialization could be implemented for this
	// class for usage in solve(), but it would be computationally inefficient

	public:
		// Constructors
		AdaptiveRKSolver(double start_step, const BaseEquation &eq,
			const std::vector<std::vector<double>> & a_,
      		const std::vector<double> & b_,
      		const std::vector<double> & c_,
			double tolerance, double minimum_step):
			RKSolver(start_step, eq, a_, b_, c_), tol(tolerance),
			hmin(minimum_step) {}
		AdaptiveRKSolver(double step, const BaseEquation &eq,
			const std::vector<std::vector<double>> & a_,
      		const std::vector<double> & b_,
      		const std::vector<double> & c_):
			AdaptiveRKSolver(step, eq, a_, b_, c_, 1e-2, step/10) {}//TODO keep?

		// Solving tool
		void solve();

		//Solution output
		void print_solver_spec() const override;
};

#endif // ADAPTIVERKSOLVER_HPP
