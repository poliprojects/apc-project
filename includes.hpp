#include "AdaptiveFESolver.hpp"
#include "AdaptiveRKSolver.hpp"
#include "BaseEquation.hpp"
#include "BaseSolver.hpp"
#include "equations.hpp"
#include "FESolver.hpp"
#include "ParallelAdaptiveIserNorSolver.hpp"
#include "ParallelIserNorSolver.hpp"
#include "RKSolver.hpp"
#include "utils.hpp"

#include <chrono>
#include <iostream>
#include <math.h>
#include <stdlib.h> // atof
#include <string>
#include <string.h> // strcmp
#include <vector>
