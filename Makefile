CXXFLAGS += -Wall -std=c++11

EXE = main
OBJS = main.o BaseEquation.o BaseSolver.o FESolver.o

.PHONY: all clean distclean

all: $(EXE)

$(EXE): $(OBJS)

main.o: FESolver.hpp BaseSolver.hpp BaseEquation.hpp
BaseEquation.o: BaseEquation.hpp
BaseSolver.o: BaseSolver.hpp BaseEquation.hpp
FESolver.o: FESolver.hpp BaseSolver.hpp BaseEquation.hpp

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
