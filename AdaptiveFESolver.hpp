#ifndef ADAPTIVEFESOLVER_HPP
#define ADAPTIVEFESOLVER_HPP

#include "BaseSolver.hpp"
#include "utils.hpp"

class AdaptiveFESolver: public FESolver{
	private:
		double tol;
		double hmin;

	public:
		// Constructors
		AdaptiveFESolver(double step, const BaseEquation &eq, double tolerance,
			double minimum_step):
			BaseSolver(step, eq), tol(tolerance), hmin(minimum_step) {}
		AdaptiveFESolver(double step, const BaseEquation &eq):
			AdaptiveFESolver(step, eq, 1e-3, step/100) {}

		// Solving tools
		double step(const double tbar, const Rnvector &ubar,
			const Rnvector &fubar) const;
		void solve();
}

#endif // ADAPTIVEFESOLVER_HPP
