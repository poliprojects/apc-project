#ifndef ADAPTIVEPARALLELISERNORSOLVER_HPP
#define ADAPTIVEPARALLELISERNORSOLVER_HPP

#include "ParallelIserNorSolver.hpp"

class AdaptiveParallelIserNorSolver: public ParallelIserNorSolver
{
    private:
        //! Error tolerance to select the step size
        double tol;

        //! Minimum step size
        double hmin;

    public:
        // Constructors
        AdaptiveParallelIserNorSolver( double step, const BaseEquation &eq,
            double tolerance, double min_step );

        //! Main solver based on Adaptive Parallel Iserles-Nørsett method
        void solve();
};


#endif // ADAPTIVEPARALLELISERNORSOLVER_HPP
