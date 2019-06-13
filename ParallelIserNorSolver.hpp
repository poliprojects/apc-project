#ifndef PARALLELISERNORSOLVER_HPP
#define PARALLELISERNORSOLVER_HPP

#include <mpi.h>
#include <chrono>
#include "RKSolver.hpp"
using namespace std::chrono;


class ParallelIserNorSolver: public RKSolver
{

    protected:
        //! One step of time integration in parallel mode, called by solve()
        Rnvector single_step( const double tn, const Rnvector &un,
            const double h ) const override;

    public:
        // Constructors
        ParallelIserNorSolver( double step, const BaseEquation &eq );
};

#endif // PARALLELISERNORSOLVER_HPP
