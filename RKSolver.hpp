#ifndef RKSOLVER_HPP
#define RKSOLVER_HPP

#include<vector>
#include<cassert>
#include "BaseSolver.hpp"


class RKSolver: public BaseSolver
{

	private:

		//! Number of time steps (known a priori, useless in adaptive version)
		unsigned Nh;

	protected:
		// Butcher tableau
		// (the vectors are of size s, the first element of c is zero;
		// the matrix is s-by-s with the upper triangular part equal to zero)
		//! a coefficients of the Butcher tableau
		std::vector<std::vector<double>> a;
		//! b coefficients of the Butcher tableau
		std::vector<double> b;
		//! c coefficients of the Butcher tableau
		std::vector<double> c;

		//! Number of stages
		unsigned n_stages;

		//! One step of time integration, called by solve()
		Rnvector single_step(const double tn, const Rnvector &un,
			const double h) const override;

	public:
    
		// Constructors
		RKSolver(double step, const BaseEquation &eq,
			const std::vector<std::vector<double>> & a_,
			const std::vector<double> & b_,
			const std::vector<double> & c_);

		//! Main solver based on Runge Kutta method
		void solve() override;

		//! Prints the characteristics of the Runge Kutta solver
		void print_solver_spec() const override;
};

#endif // RKSOLVER_HPP
