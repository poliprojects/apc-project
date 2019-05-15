#ifndef BASEEQUATION_HPP
#define BASEEQUATION_HPP

#include "utils.hpp"


class BaseEquation
{
	private:
		double tin;
		double tfin;
		EquationFunction & f;
		Rnvector x0;
		unsigned dimension; // dimension of the system (x0.size())

	public:
		// Constructors
		BaseEquation(const double &initial_time, const double &final_time,
			EquationFunction &fun, const Rnvector &initial_cond):
			tin(initial_time), tfin(final_time), f(fun), x0(initial_cond)
			{ dimension = x0.size(); }

		// Getters
		EquationFunction & get_f() const { return f; };
		double get_tin() const { return tin; };
		double get_tfin() const { return tfin; };
		Rnvector get_x0() const { return x0; };
		unsigned get_dimension() const { return dimension; };

		// Setters
		void set_f(EquationFunction & fun) { f = fun; };
		void set_tin(const double &initial_time) { tfin = initial_time; };
		void set_tfin(const double &final_time) { tfin = final_time; };
		void set_x0(const Rnvector &initial_cond) { x0 = initial_cond; };
		void set_dimension(const double & dim) { dimension = dim; };
};

#endif //BASEEQUATION_HPP
