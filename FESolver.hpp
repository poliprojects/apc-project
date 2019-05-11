#ifndef FESOLVER_HPP
#define FESOLVER_HPP

#include "BaseSolver.hpp"


class FESolver: public BaseSolver
{
	public:
		// Constructors
		FESolver(double step, const BaseEquation &eq): BaseSolver(step, eq) {}

		// Solving tools
		double step() const override;
		void solve() override;
};

#endif // FESOLVER_HPP
