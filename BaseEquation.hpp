//#include...

class BaseEquation{
	typedef std::vector<double> Rnvector;

	private:
		double tfin;
		EquationFunction f;
		Rnvector x0;
		BaseSolver solver;
	public:
		double get_tfin() const;
		EquationFunction get_f() const;
		Rnvector get_x0() const;

		void set_tfin();
		void set_f();
		void set_x0();

}
