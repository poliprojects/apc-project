CXX = mpicxx
CXXFLAGS += -Wall -std=c++11 \
   -Werror \
   -Wextra \
   -Wconversion \
   -Wno-deprecated \
   -Winit-self \
   -Wsign-conversion \
   -Wredundant-decls \
   -Wvla -Wshadow -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual \
   -Winit-self \
   -Wpointer-arith \
   -Wcast-qual \
   -Wcast-align \
   -Wdouble-promotion \
   -Wold-style-cast -Wno-error=old-style-cast \
   -Wsign-promo \
   -Wswitch-enum \
   -Wswitch-default \
   -Wundef


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
