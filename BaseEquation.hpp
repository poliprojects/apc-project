#include"utils.hpp"

class BaseEquation{

	private:
		double tfin;
		EquationFunction f;
		Rnvector x0;

	public:
		BaseEquation(const double & final_time, const EquationFunction & fun, const Rnvector & initial_condition):
			tfin(final_time), f(fun), x0(initial_condition) {}

		// double get_tfin() const;
		// EquationFunction get_f() const;
		// Rnvector get_x0() const;
		// void set_tfin();
		// void set_f();
		// void set_x0();

}
