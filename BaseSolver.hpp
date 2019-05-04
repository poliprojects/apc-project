#ifndef BASESOLVER_HPP
#define BASESOLVER_HPP

#include"BaseEquation.hpp"

class BaseSolver{

	protected:
		double h;
		BaseEquation equation;

	public:
		BaseSolver(double step, const BaseEquation & eq): h(step), equation(eq) {}
		// double get_step0() const;
		// void set_step0();
		virtual double step() const = 0;
		virtual void solve() = 0;
};

#endif
