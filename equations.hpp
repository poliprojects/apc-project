#ifndef EQUATIONS_HPP
#define EQUATIONS_HPP

#include "utils.hpp"


struct EquationFunction
{
	EquationFunction(const std::string f_expr): f_string(f_expr) {}
	EquationFunction() = default;
	virtual ~EquationFunction() = default;
	virtual Rnvector operator()(const double & t, Rnvector y) const = 0;
	std::string f_string;
};


// Examples of test equations
struct EquationFunction_1: public EquationFunction
{
	Rnvector operator()(const double & t, Rnvector y) const override;
	EquationFunction_1(): EquationFunction("y'(t) = 5*y(t) - 3") {}
};

struct EquationFunction_2: public EquationFunction
{
	Rnvector operator()(const double & t, Rnvector y) const override;
	EquationFunction_2(): EquationFunction("y'(t) = -y(t)") {}
};

struct EquationFunction_3: public EquationFunction
{
	Rnvector operator()(const double & t, Rnvector y) const override;
	EquationFunction_3(): EquationFunction("y'(t) = t - y(t)") {}
};

struct EquationFunction_4: public EquationFunction
{
	Rnvector operator()(const double & t, Rnvector y) const override;
	EquationFunction_4(): EquationFunction(
	"y1'(t) = -3*y1(t) -   y2(t) + sin(t)\ny2'(t) =    y1(t) - 5*y2(t) - 2\t")
	{} //TODO
};

#endif // EQUATIONS_HPP
