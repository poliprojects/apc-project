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
		AdaptiveRKSolver( double start_step, const BaseEquation &eq,
			const std::vector<std::vector<double>> &a_,
      		const std::vector<double> &b_,
      		const std::vector<double> &c_,
			double tolerance, double min_step ):
			RKSolver( start_step, eq, a_, b_, c_ ), tol( tolerance ),
			hmin( min_step ) {}
		AdaptiveRKSolver( double start_step, const BaseEquation &eq,
			std::string name, double tolerance, double min_step ):
			RKSolver( start_step, eq, name ), tol( tolerance ),
			hmin( min_step ) {}

		// Solving tool
		void solve();

		//Solution output
		void print_solver_spec() const override;
};

#endif // ADAPTIVERKSOLVER_HPP
