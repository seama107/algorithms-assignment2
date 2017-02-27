OBJ= DFAtranslator.cpp NFA.cpp transitionFunction.cpp vectorFunctions.cpp

DFAtranslator: $(OBJ)
	g++ -std=c++11 *.cpp
