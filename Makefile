CXXFLAGS += -Wall -std=c++11

EXE = main
OBJS = main.o FESolver.o

.PHONY: all clean distclean

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT_OPTION)

main.o: FESolver.hpp BaseSolver.hpp BaseEquation.hpp
FESolver.o: FESolver.hpp BaseSolver.hpp BaseEquation.hpp

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
