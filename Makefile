CC=g++
CFLAGS= -std=c++11
DEPS= NFA.h transitionFunction.h vectorFunctions.h
OBJ= DFAtranslator.o NFA.o transitionFunction.o vectorFunctions.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

DFAtranslator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
