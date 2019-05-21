#ifndef RKSOLVER_HPP
#define RKSOLVER_HPP

#include<vector>
#include<cassert>
#include "BaseSolver.hpp"


class RKSolver: public BaseSolver
{
  private:
    unsigned Nh; //number of steps: ( Tf - T0 ) / h;

  protected:
    // Butcher array
    // (the vectors are of size s, the first element of c is zero;
    // the matrix is s-by-s with the upper triangular part equal to zero)
    std::vector<std::vector<double>> a;
    std::vector<double> b;
    std::vector<double> c;

    // Stages
    unsigned n_stages;

    // Solving tools
    Rnvector single_step(const double tn, const Rnvector &un,
      const double h) const override;

  public:
    // Constructors
    RKSolver(double step, const BaseEquation &eq,
      const std::vector<std::vector<double>> & a_,
      const std::vector<double> & b_,
      const std::vector<double> & c_);

    // Solving tools
  	double step() const override;
  	void solve() override;

    //Solution output
		void print_solver_spec() const override;
};

#endif // RKSOLVER_HPP
