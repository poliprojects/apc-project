#ifndef BASESOLVER_HPP
#define BASESOLVER_HPP

#include<iostream>
#include<fstream>
#include"BaseEquation.hpp"
#include"utils.hpp"

class BaseSolver
{
	protected:
		double h;
		unsigned Nh;
		BaseEquation equation;
		SolutionType solution;	//default constructed as an empty vector of vectors

	public:
		BaseSolver(double step, const BaseEquation & eq);

		unsigned get_Nh() const { return Nh; };
		SolutionType get_solution() const { return solution; };

		void print() const;
		void save_sol_to_file(const std::string & file_name) const;

		virtual double step() const = 0;
		virtual void solve() = 0;
};

#endif
