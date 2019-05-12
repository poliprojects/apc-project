CXXFLAGS += -Wall -std=c++11
CPPFLAGS += -DTEST_3

EXE = main
SOLVERS = BaseSolver.o FESolver.o AdaptiveFESolver.o
OBJS = $(SOLVERS) main.o

.PHONY: all clean distclean

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT_OPTION)

# $(OBJS): BaseEquation.hpp BaseSolver.hpp utils.hpp
BaseSolver.o: BaseEquation.hpp BaseSolver.hpp utils.hpp
FESolver.o: BaseEquation.hpp BaseSolver.hpp FESolver.hpp utils.hpp
AdaptiveFESolver.o: BaseEquation.hpp BaseSolver.hpp FESolver.hpp AdaptiveFESolver.hpp utils.hpp
main.o: BaseEquation.hpp BaseSolver.hpp FESolver.hpp AdaptiveFESolver.o utils.hpp


clean:
	$(RM) *.o

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
