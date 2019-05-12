#ifndef FESOLVER_HPP
#define FESOLVER_HPP

#include "BaseSolver.hpp"


class FESolver: public BaseSolver
{
	private:
		unsigned Nh; //number of steps: ( Tf - T0 ) / h;

	public:
		// Constructors
		FESolver(double step, const BaseEquation &eq);

		// Getters
		unsigned get_Nh() const { return Nh; };

		// Solving tool
		void solve() override;

		//Solution output
		void print_solver_spec() const override;
};

#endif // FESOLVER_HPP
