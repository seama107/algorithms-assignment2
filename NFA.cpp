#include "NFA.h"

using namespace std;

NFA::NFA() {
  //Builds the trivial machine that accepts any binary string
  states = {"q1", "q2"};
  alphabet = {"0", "1"};

  startState = "q1";
  acceptStates = {"q2"};
  transitionFunctions = {
    transitionFunction {"q1", "0", "q2"},
    transitionFunction {"q1", "1", "q2"},
    transitionFunction {"q1", "EPS", "q2"},
    transitionFunction {"q2", "0", "q2"},
    transitionFunction {"q2", "1", "q2"},
  };


}

NFA::NFA(set<string> q,
    set<string> s,
    string start,
    set<string> f,
    set<transitionFunction> d) {
  states = q;
  alphabet = s;
  startState = start;
  acceptStates = f;
  transitionFunctions = d;
}

void printStringSet(set<string> inputset) {
  for(string s :inputset ) {
    cout << s << "\n";
  }
  return;
}

NFA NFA::translateToDFA() {
  //The main function of this assignment: translates NFAs to DFAs
  //First setting up the variables that define our machine
  set<string> dStates = {"EM"};
  set<string> dAlphabet = (this->alphabet);
  string dStartState;
  set<string> dAcceptStates = {};
  set<transitionFunction> dTransitionFunctions = {};

  set<string> currentState = {this->startState};
  currentState = epsilonClosureOfState(currentState);
  dStartState = generateStateName(currentState);

  //This keeps track of what states have already been calculated, so
  //no repeats are done in the while loop - possibly leading to an
  //infinite loop
  set<set<string>> statesAlreadyCalculated = {};
  vector<set<string>> statesToCalculateStack = {};
  statesToCalculateStack.push_back(currentState);

  while(statesToCalculateStack.size() > 0 ) {
    //Pulls the most recent addition of a state from statesToCalculateStack
    currentState = statesToCalculateStack.back();
    statesToCalculateStack.pop_back();
    if(currentState.size() == 0) {
      //Making sure an empty state is not recieved
      cout << "ERROR: Just tried to calculate options from an empty state" << "\n";
      continue;
    }
    string stateName = generateStateName(currentState);
    dStates.insert(stateName);

    bool isAcceptState = setIntersect(currentState, this->acceptStates).size() > 0;
    if(isAcceptState) {
      dAcceptStates.insert(stateName);
    }

    //Creating a transitionFunction for every symbol for every reachable state
    for(string symbol : this->alphabet) {
      set<string> nextState = {};
      for(string substate : currentState) {
        transitionFunction departureFunction = {substate, symbol, "*"};
        set<transitionFunction> transitionsFromSubstate = subsetWhereEquals(this->transitionFunctions, departureFunction);
        for(transitionFunction tf : transitionsFromSubstate) {
          nextState.insert(tf.finalState);
        }
      }

      //Put logic for pushing new things to calculate on the stack here
      //remember for each one to check if it's an empty state - if it is
      //then don't put it on the stack (but do make a transitionFunction
      // to -> send it to EM). if it isn't, calculate the epsilon
      //closure, and then check if that state is a member of statesAlreadyCalculated
      //if not, then put that state on the stack

      transitionFunction deterministicTransition;

      if(nextState.size() == 0) {
        deterministicTransition = transitionFunction {stateName, symbol, "EM"};
      }
      else {
        nextState = epsilonClosureOfState(nextState);
        string nextStateName = generateStateName(nextState);
        deterministicTransition = transitionFunction {stateName, symbol, nextStateName};
        bool alreadyCalculated = statesAlreadyCalculated.find(nextState) != statesAlreadyCalculated.end();
        if(!(alreadyCalculated)) {
          statesToCalculateStack.push_back(nextState);
        }
        else {
          cout << "Already calculated " << nextStateName << "\n";
        }
      }

      dTransitionFunctions.insert(deterministicTransition);
    }
    statesAlreadyCalculated.insert(currentState);

  }



  return NFA(dStates, dAlphabet, dStartState, dAcceptStates, dTransitionFunctions);
}



set<string> NFA::epsilonClosureOfState(set<string> currentState) {
  //find all transitionFunctions whose initial state is a membet of
  //the current state and whose symbol is epsilon, and then appends
  //currentState to hold the output of those transitionFunctions
  set<transitionFunction> possibleTransitionFunctions = {};
  for(string state : currentState) {
    possibleTransitionFunctions.insert( transitionFunction {state, "EPS", "*"} );
  }
  set<transitionFunction> epsilonTransitions = setIntersect(this->transitionFunctions, possibleTransitionFunctions);
  //the set 'epsilonTransitions' now holds transitionFunctions such that
  //their inputSymbol == "EPS" and their state is a member of currentState
  int numberOfSubstates = currentState.size();
  for(transitionFunction tf : epsilonTransitions) {
    currentState.insert(tf.finalState);
  }
  if(numberOfSubstates != currentState.size()) {
    //If the state was updated, we need to calculate the EC of the new state
    return epsilonClosureOfState(currentState);
  }
  return currentState;
}

string NFA::generateStateName(set<string> currentState) {
  //Creates the fancy formatting for sets of states
  stringstream ss;
  ss << "{";
  set<string>::iterator it;
  for(it = currentState.begin(); it != currentState.end(); it++) {
    if(it != currentState.begin()) {
      ss << ", ";
    }
    ss << *it;
  }
  ss << "}";
  return ss.str();
}




ostream& operator<<(ostream& out, const NFA& t)
{
  for(string state : t.states) {
    out << state << "\t";
  }
  out << "\n";

  for(string x : t.alphabet) {
    out << x << "\t";
  }
  out << "\n";

  out << t.startState << "\n";

  for(string state : t.acceptStates) {
    out << state << "\t";
  }
  out << "\n";

  for(transitionFunction f : t.transitionFunctions) {
    out << f << "\n";
  }

  return out;
}
