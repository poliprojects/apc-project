CXXFLAGS += -Wall -std=c++11
CPPFLAGS += -DTEST_1

EXE = main
SOLVERS = BaseSolver.o FESolver.o AdaptiveFESolver.o RKSolver.o \
	AdaptiveRKSolver.o
OBJS = $(SOLVERS) main.o utils.o

.PHONY: all clean distclean

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT_OPTION)

$(OBJS): BaseEquation.hpp BaseSolver.hpp utils.hpp
utils.o: utils.hpp
main.o: FESolver.hpp AdaptiveFESolver.hpp RKSolver.hpp AdaptiveRKSolver.hpp
FESolver.o: FESolver.hpp
AdaptiveFESolver.o: FESolver.hpp AdaptiveFESolver.hpp
RKSolver.o: RKSolver.hpp
AdaptiveRKSolver.o: RKSolver.hpp AdaptiveRKSolver.hpp

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
