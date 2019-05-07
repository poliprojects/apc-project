#ifndef BASEEQUATION_HPP
#define BASEEQUATION_HPP

#include"utils.hpp"

class BaseEquation
{
	private:
		double tin;
		double tfin;
		EquationFunction f;
		Rnvector x0;

	public:
		BaseEquation(const double & final_time, const EquationFunction & fun, const Rnvector & initial_condition):
			tin(0), tfin(final_time), f(fun), x0(initial_condition) {}
		BaseEquation(const double & initial_time, const double & final_time, const EquationFunction & fun, const Rnvector & initial_condition):
			tin(initial_time), tfin(final_time), f(fun), x0(initial_condition) {}

		EquationFunction get_f() const { return f; };
		double get_tfin() const { return tfin; };
		double get_tin() const { return tin; };
		Rnvector get_x0() const { return x0; };
};

#endif
