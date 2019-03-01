CXXFLAGS += -Wall -std=c++11

EXE = main
OBJS = main.o

.PHONY: all clean distclean

all: $(EXE)

clean:
	$(RM) *.o

distclean: clean
	$(RM) $(EXE)
	$(RM) *~
