#ifndef BASEEQUATION_HPP
#define BASEEQUATION_HPP

#include "equations.hpp"


class BaseEquation
{

    private:

        //! Inital time
        double tin;

        //! Final time
        double tfin;

        //! Right hand side f(x,t)
        EquationFunction &f;

        //! Initial condition
        Rnvector x0;

        //! Dimension of the system (x0.size())
        unsigned dimension;

    public:

        // Constructors
        BaseEquation( const double &initial_time, const double &final_time,
            EquationFunction &fun, const Rnvector &initial_cond ):
            tin( initial_time ), tfin( final_time ), f( fun ),
            x0( initial_cond ) { dimension = x0.size(); }

        // Getters
        EquationFunction &get_f() const { return f; };
        double get_tin() const { return tin; };
        double get_tfin() const { return tfin; };
        Rnvector get_x0() const { return x0; };
        unsigned get_dimension() const { return dimension; };

        // Setters
        void set_f( EquationFunction &fun ) { f = fun; };
        void set_tin( const double &initial_time ) { tfin = initial_time; };
        void set_tfin( const double &final_time ) { tfin = final_time; };
        void set_x0( const Rnvector &cond )
            { x0 = cond; dimension = x0.size(); };
};

#endif //BASEEQUATION_HPP
