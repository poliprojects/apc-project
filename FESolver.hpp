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

		// Solving tools
		double step() const override;
		void solve() override;

		//Solution output
		void print_solver_spec() const override;
};

#endif // FESOLVER_HPP
