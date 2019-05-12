#ifndef ADAPTIVEFESOLVER_HPP
#define ADAPTIVEFESOLVER_HPP

#include "FESolver.hpp"


class AdaptiveFESolver: public FESolver
{
	private:
		double tol;
		double hmin;
		// in this class, h is the starting value for the step and Nh has no
		// meaning

	public:
		// Constructors
		AdaptiveFESolver(double start_step, const BaseEquation &eq,
			double tolerance, double minimum_step):
			FESolver(start_step, eq), tol(tolerance), hmin(minimum_step) {}
		AdaptiveFESolver(double step, const BaseEquation &eq):
			AdaptiveFESolver(step, eq, 1e-2, step/10) {} // keep?

		// Solving tools
		double step(const double tbar, const Rnvector &ubar,
			const Rnvector &fubar) const;
		void solve();

		void print() const override;
};

#endif // ADAPTIVEFESOLVER_HPP
