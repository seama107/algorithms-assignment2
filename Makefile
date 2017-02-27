CC=g++
CFLAGS= -std=c++11
OBJ= DFAtranslator.o NFA.o transitionFunction.o vectorFunctions.o

DFAtranslator: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)
