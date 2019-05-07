CXXFLAGS += -Wall -std=c++11
CPPFLAGS += -DTEST_3

EXE = main
OBJS = main.o FESolver.o BaseSolver.o

.PHONY: all clean distclean

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT_OPTION)

main.o: FESolver.hpp BaseSolver.hpp BaseEquation.hpp utils.hpp
FESolver.o: FESolver.hpp BaseSolver.hpp BaseEquation.hpp utils.hpp
BaseSolver.o: BaseSolver.hpp BaseEquation.hpp utils.hpp

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
