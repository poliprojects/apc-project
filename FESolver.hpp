#ifndef FESOLVER_HPP
#define FESOLVER_HPP

#include "BaseSolver.hpp"


class FESolver: public BaseSolver
{

	protected:

		//! One step of time integration, called by solve()
		Rnvector single_step(const double tn, const Rnvector &un,
			const double h) const override;

	public:

		// Constructors
		FESolver(double step, const BaseEquation &eq);

		// Getters
		unsigned get_Nh() const { return Nh; };

		//! Main solver based on Forward Euler method
		void solve() override;

		//! Prints the characteristics of the Forward Euler solver
		void print_solver_spec() const override;
};

#endif // FESOLVER_HPP
