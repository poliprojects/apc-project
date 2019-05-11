#ifndef BASEEQUATION_HPP
#define BASEEQUATION_HPP

#include "utils.hpp"


class BaseEquation
{
	private:
		double tin;
		double tfin;
		EquationFunction f;
		Rnvector x0;

	public:
		// Constructors
		BaseEquation(const double &initial_time, const double &final_time,
			const EquationFunction &fun, const Rnvector &initial_cond):
			tin(initial_time), tfin(final_time), f(fun), x0(initial_cond) {}

		BaseEquation(const double &final_time, const EquationFunction &fun,
			const Rnvector &initial_condition):
			BaseEquation(0.0, final_time, fun, initial_condition) {}
			//tin(0), tfin(final_time), f(fun), x0(initial_condition) {}

		// Getters and setters
		EquationFunction get_f() const { return f; };
		double get_tin() const { return tin; };
		double get_tfin() const { return tfin; };
		Rnvector get_x0() const { return x0; };

		void set_f(const EquationFunction &fun) { f = fun; }; //?
		void set_tin(const double &initial_time) { tfin = initial_time; };
		void set_tfin(const double &final_time) { tfin = final_time; };
		void set_x0(const Rnvector &initial_cond) { x0 = initial_cond };
};

#endif //BASEEQUATION_HPP
