#ifndef FESOLVER_HPP
#define FESOLVER_HPP

#include "BaseSolver.hpp"
#include"utils.hpp"

class FESolver: public BaseSolver
{
	public:
		FESolver(double step, const BaseEquation & eq): BaseSolver(step, eq) {}
		double step() const override;
		void solve() override;
};

#endif
