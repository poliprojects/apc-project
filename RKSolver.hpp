#ifndef RKSOLVER_HPP
#define RKSOLVER_HPP

#include<vector>
#include<cassert>
#include<cstdlib>
#include<string>
#include "BaseSolver.hpp"


class RKSolver: public BaseSolver
{

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

    //! Name of the RK method
    std::string method_name;

    //! Tolerance for fixed point iterations (in case of implicit method)
    double fixed_point_tol = 0.001;

    //! One step of time integration, called by solve()
    Rnvector single_step( const double tn, const Rnvector &un,
      const double h ) const override;

    //! Computes the K-th coefficient for an implicit method
    Rnvector fixed_point( const EquationFunction &f, const double tn,
      const Rnvector &un, const Rnvector &sum_aij_Kj, const size_t i ) const;

    //! Computes the error at a certain iteration of the fixed point algorithm
    double compute_error( const Rnvector &K0, const Rnvector &K1 ) const;

    //! Checks if the K-th coefficient computation is implicit looking at A
    bool is_implicit( const size_t K_index ) const;

  public:

    // Constructors
    RKSolver( double step, const BaseEquation &eq,
      const std::vector<std::vector<double>> &a_,
      const std::vector<double> &b_,
      const std::vector<double> &c_ );
    RKSolver( double step, const BaseEquation &eq, const std::string name );

		//! Main solver based on Runge Kutta method
		void solve() override;

		//! Prints the characteristics of the Runge Kutta solver
		void print_solver_spec() const override;
};

#endif // RKSOLVER_HPP
