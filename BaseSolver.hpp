//#include...

class BaseSolver{
	private:
		double step0;
		BaseEquation equation;
		

	public:
		double get_step0() const;
		void set_step0();
		virtual double step() = 0;
		virtual void solve() = 0;
}
