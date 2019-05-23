#ifndef BASESOLVER_HPP
#define BASESOLVER_HPP

#include <iostream>
#include <fstream>
#include "BaseEquation.hpp"


class BaseSolver
{
	protected:
		double h; //assumption: h divides Tf-T0 exactly
		BaseEquation equation;
		SolutionType solution; // default constructed as empty vector of vectors
		std::vector<double> times; // at the end contains the time instants

		// Solving tools
		virtual Rnvector single_step(const double tn, const Rnvector &un,
			const double h) const = 0;

	public:
		// Constructors and destructors
		BaseSolver(double step, const BaseEquation &eq);
		virtual ~BaseSolver() = default;

		// Getters
		double get_h() const { return h; };
		BaseEquation get_equation() const { return equation; };
		SolutionType get_solution() const { return solution; };

		// Solving tools
		virtual void solve() = 0;

		// Solution output
		virtual void print() const;
		virtual void print_solver_spec() const = 0;
		virtual void save_sol_to_file(const std::string &file_name) const;
};

#endif // BASESOLVER_HPP
