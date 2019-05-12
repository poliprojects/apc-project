CXXFLAGS += -Wall -std=c++11
CPPFLAGS += -DTEST_3

EXE = main
SOLVERS = BaseSolver.o FESolver.o AdaptiveFESolver.o RKSolver.o
OBJS = $(SOLVERS) main.o utils.o

.PHONY: all clean distclean

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(OUTPUT_OPTION)

$(OBJS): BaseEquation.hpp BaseSolver.hpp utils.hpp
utils.o: utils.hpp
main.o: FESolver.hpp AdaptiveFESolver.hpp RKSolver.hpp
FESolver.o: FESolver.hpp
AdaptiveFESolver.o: FESolver.hpp AdaptiveFESolver.hpp
RKSolver.o: RKSolver.hpp


clean:
	$(RM) *.o

distclean: clean
	$(RM) $(EXE)
	$(RM) *~

# CXXFLAGS += -Wall -std=c++11
# CPPFLAGS += -DTEST_3
#
# EXE = testRKmain
# SOLVERS = BaseSolver.o RKSolver.o
# OBJS = $(SOLVERS) testRKmain.o utils.o
#
# .PHONY: all clean distclean
#
# all: $(EXE)
#
# $(EXE): $(OBJS)
# 	$(CXX) $(CXXFLAGS) $^ $(OUTPUT_OPTION)
#
# $(OBJS): BaseEquation.hpp BaseSolver.hpp utils.hpp
# utils.o: utils.hpp
# testRKmain.o: RKSolver.hpp
#
#
#
# clean:
# 	$(RM) *.o
#
# distclean: clean
# 	$(RM) $(EXE)
# 	$(RM) *~
