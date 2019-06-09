#ifndef ADAPTIVEFESOLVER_HPP
#define ADAPTIVEFESOLVER_HPP

#include "FESolver.hpp"


class AdaptiveFESolver: public FESolver
{

	private:

		//! Error tolerance to select the step size
		double tol;

		//! Minimum step size
		double hmin;

	public:

		// Constructors
		AdaptiveFESolver( double start_step, const BaseEquation &eq,
			double tolerance, double min_step ):
			FESolver( start_step, eq ), tol( tolerance ), hmin( min_step ) {}

		//! Main solver based on Adaptive Forward Euler method
		void solve();

		//! Prints the characteristics of the Adaptive Forward Euler solver
		void print_solver_spec() const override;
};

#endif // ADAPTIVEFESOLVER_HPP
