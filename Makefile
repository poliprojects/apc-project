CXXFLAGS += -Wall -std=c++11
CPPFLAGS += -DTEST_3

EXE = main
SOLVERS = BaseSolver.o FESolver.o AdaptiveFESolver.o
OBJS = $(SOLVERS) main.o

.PHONY: all clean distclean

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT_OPTION)

$(OBJS): BaseEquation.hpp BaseSolver.hpp utils.hpp
main.o: FESolver.hpp AdaptiveFESolver.o
FESolver.o: FESolver.hpp
AdaptiveFESolver.o: FESolver.hpp AdaptiveFESolver.hpp

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(EXE)
	$(RM) *~

