#ifndef ADAPTIVERKSOLVER_HPP
#define ADAPTIVERKSOLVER_HPP

#include "RKSolver.hpp"
#include <cmath>


class AdaptiveRKSolver: public RKSolver
{
    private:
        //! Error tolerance to select the step size
        double tol;

        //! Minimum step size
        double hmin;

        //! Maximum step size (useful if implicit because of fixed point)
        double hmax;

    public:
        // Constructors
        AdaptiveRKSolver( double start_step, const BaseEquation &eq,
            const std::vector<std::vector<double>> &a_,
            const std::vector<double> &b_,
            const std::vector<double> &c_,
            double tolerance, double min_step, double max_step ):
            RKSolver( start_step, eq, a_, b_, c_ ), tol( tolerance ),
            hmin( min_step ), hmax( max_step ) {}
        AdaptiveRKSolver( double start_step, const BaseEquation &eq,
            std::string name, double tolerance, double min_step,
            double max_step ):
            RKSolver( start_step, eq, name ), tol( tolerance ),
            hmin( min_step ), hmax( max_step ) {}

        //! Main solver based on Adaptive Runge-Kutta method
        void solve();

        //! Prints the characteristics of the Adaptive Runge-Kutta solver
        void print_solver_spec() const override;
};


#endif // ADAPTIVERKSOLVER_HPP
