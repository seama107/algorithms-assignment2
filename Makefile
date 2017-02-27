CC=g++
CFLAGS= -std=c++11 -w
OBJ= DFAtranslator.o NFA.o transitionFunction.o vectorFunctions.o

DFAtranslator: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)
