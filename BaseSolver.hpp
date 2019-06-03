#ifndef BASESOLVER_HPP
#define BASESOLVER_HPP

#include <iostream>
#include <fstream>
#include "BaseEquation.hpp"


class BaseSolver
{

	protected:

		//! Integration step (starting value in adaptive methods)
		double h;

		//! Equation to be solved
		BaseEquation equation;

		//! Solution (to be filled by solve())
		SolutionType solution;

		//! Time instants (to be filled by solve())
		std::vector<double> times;

		//! One step of time integration
		virtual Rnvector single_step(const double tn, const Rnvector &un,
			const double h) const = 0;

	public:

		// Constructors
		BaseSolver(double step, const BaseEquation &eq);

		// Destructor
		virtual ~BaseSolver() = default;

		// Getters
		double get_h() const { return h; };
		BaseEquation get_equation() const { return equation; };
		SolutionType get_solution() const { return solution; };

		//! Main solver
		virtual void solve() = 0;

		//! Prints the equation and calls print_solver_spec()
		virtual void print() const;
		//! Prints the characteristics of the solver chosen
		virtual void print_solver_spec() const = 0;

		//! Saves solution and time instants in a .txt file
		virtual void save_sol_to_file(const std::string &file_name) const;
};

#endif // BASESOLVER_HPP
