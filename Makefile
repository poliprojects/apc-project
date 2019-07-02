CXX = mpicxx
CXXFLAGS += -Wall -std=c++11

EXE = main
SOLVERS = BaseSolver.o FESolver.o AdaptiveFESolver.o RKSolver.o \
	AdaptiveRKSolver.o ParallelIserNorSolver.o ParallelAdaptiveIserNorSolver.o
OBJS = $(SOLVERS) main.o utils.o equations.o RuntimeUtils.o

.PHONY: all clean distclean

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT_OPTION)

$(OBJS): BaseEquation.hpp BaseSolver.hpp equations.hpp RuntimeUtils.hpp
main.o: FESolver.hpp AdaptiveFESolver.hpp RKSolver.hpp AdaptiveRKSolver.hpp \
	ParallelIserNorSolver.hpp ParallelAdaptiveIserNorSolver.hpp
FESolver.o: FESolver.hpp
AdaptiveFESolver.o: AdaptiveFESolver.hpp
RKSolver.o: RKSolver.hpp
AdaptiveRKSolver.o: AdaptiveRKSolver.hpp
ParallelIserNorSolver.o: ParallelIserNorSolver.hpp
ParallelAdaptiveIserNorSolver.o: ParallelAdaptiveIserNorSolver.hpp

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
