#ifndef PARALLELADAPTIVEISERNORSOLVER_HPP
#define PARALLELADAPTIVEISERNORSOLVER_HPP

#include "ParallelIserNorSolver.hpp"


class ParallelAdaptiveIserNorSolver: public ParallelIserNorSolver
{
    private:
        //! Error tolerance to select the step size
        double tol;

        //! Minimum step size
        double hmin;

    public:
        // Constructors
        ParallelAdaptiveIserNorSolver( double step, const BaseEquation &eq,
            double tolerance, double min_step );

        //! Main solver based on Adaptive Parallel Iserles-Nørsett method
        void solve();
};


#endif // PARALLELADAPTIVEISERNORSOLVER_HPP
