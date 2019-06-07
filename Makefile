CXXFLAGS += -Wall -std=c++11

EXE = main
SOLVERS = BaseSolver.o FESolver.o AdaptiveFESolver.o RKSolver.o \
	AdaptiveRKSolver.o RK4Solver.o
OBJS = $(SOLVERS) main.o utils.o equations.o

.PHONY: all clean distclean

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT_OPTION)

$(OBJS): BaseEquation.hpp BaseSolver.hpp equations.hpp
main.o: FESolver.hpp AdaptiveFESolver.hpp RKSolver.hpp AdaptiveRKSolver.hpp \
	RK4Solver.hpp
FESolver.o: FESolver.hpp
AdaptiveFESolver.o: FESolver.hpp AdaptiveFESolver.hpp
RKSolver.o: RKSolver.hpp
AdaptiveRKSolver.o: RKSolver.hpp AdaptiveRKSolver.hpp
RK4Solver.o: RKSolver.hpp RK4Solver.hpp

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
