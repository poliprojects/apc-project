//#include...

class BaseSolver{
	private:
		double step0;

	public:
		double get_step0() const;
		void set_step0();
		virtual double step() = 0;
}
