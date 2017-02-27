#ifndef NFA_h
#define NFA_h

#include <string>
#include <iostream>
#include <set>
#include "vectorFunctions.h"
#include "transitionFunction.h"

class NFA
{
private:
  std::set<std::string> states;
  std::set<std::string> alphabet;
  std::string startState;
  std::set<std::string> acceptStates;
  std::set<transitionFunction> transitionFunctions;

public:
  NFA();
  NFA(std::set<std::string> states,
    std::set<std::string> alphabet,
    std::string startState,
    std::set<std::string> acceptStates,
    std::set<transitionFunction> transitionFunctions);

  NFA translateToDFA();
  std::set<std::string> epsilonClosureOfState(std::set<std::string> currentState);
  std::string generateStateName(std::set<std::string> currentState);

  friend std::ostream& operator<<(std::ostream& out, const NFA&);

};

#endif
