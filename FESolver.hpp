#include "BaseSolver.hpp"

class FESolver: public BaseSolver{

	public:
		FESolver(double step, const BaseEquation & eq): BaseSolver(step, eq) {}
		double step() override;
}
