#ifndef BASESOLVER_HPP
#define BASESOLVER_HPP

#include<iostream>
#include<fstream>
#include "BaseEquation.hpp"
#include "utils.hpp"

class BaseSolver
{
	protected: //or private???
		double h;
		unsigned Nh;
		BaseEquation equation;
		SolutionType solution; // default constructed as empty vector of vectors

	public:
		// Constructor
		BaseSolver(double step, const BaseEquation &eq);

		// Getters
		unsigned get_Nh() const { return Nh; };
		SolutionType get_solution() const { return solution; };

		// Solving tools
		virtual double step() const = 0;
		virtual void solve() = 0;

		// Solution output
		void print() const;
		void save_sol_to_file(const std::string &file_name) const;
};

#endif // BASESOLVER_HPP
