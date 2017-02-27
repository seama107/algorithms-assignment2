#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include "NFA.h"
#include "vectorFunctions.h"

using namespace std;


string promptForFilename(int argc, char const *argv[]);
NFA createNFAromInputFile(ifstream &NFAFile);
string removeBrackets(string state);



int main(int argc, char const *argv[]) {
  cout << "Welcome to the NFA-DFA translator.\n";
  cout << "The program that translates non-deterministic finite state\n";
  cout << "automata into their deterministic-equivilant counterpart.\n\n\n";

  string inFileName = promptForFilename(argc, argv);
  NFA inputNFA;
  ifstream NFAFile (inFileName);
  if(NFAFile.is_open()) {
    inputNFA = createNFAromInputFile(NFAFile);
    NFAFile.close();
  }
  else {
    cout << "Could not open file " << inFileName <<"\n";
    return 0;
  }

  cout << inputNFA << "\n-------------------------\n\n";

  NFA outputDFA = inputNFA.translateToDFA();

  cout << "\n-------------------------\n\n" << "Equivalent DFA:\n";
  cout << outputDFA << "\n";

  string::size_type const p (inFileName.find_last_of('.'));
  string outFileName = inFileName.substr(0, p).append(".DFA");
  ofstream DFAFile (outFileName);

  if(DFAFile.is_open()) {
    DFAFile << outputDFA;
    DFAFile.close();
  }
  else {
    cout << "Could not write to file " << outFileName <<"\n";
  }

  return 0;
}

string promptForFilename(int argc, char const *argv[]) {
  string filename;

  if(argc > 1) {
    filename = string(argv[1]);
  }
  else {
    cout << "Enter the filename for the NFA that you want converted:\n";
    cin >> filename;
  }
  return filename;
}

string removeBrackets(string state) {
  if(state[0] == '{' && state[state.size() - 1] == '}') {
    state.erase(0, 1);
    state.erase(state.size() - 1);
  }
  return state;
}

NFA createNFAromInputFile(ifstream &NFAFile) {
  // Parses through the file, line by line picking up the
  // set of states, alphabet, start state, accept states, and
  // the transition function
  string line;
  getline(NFAFile, line);
  vector<string> lineSplit = split(line, '\t');
  for_each(lineSplit.begin(), lineSplit.end(), &removeBrackets );
  set<string> states = convertToSet( lineSplit );

  getline(NFAFile, line);
  set<string> alphabet = convertToSet( split(line, '\t') );

  string startState;
  getline(NFAFile, startState);
  startState = removeBrackets(startState);

  getline(NFAFile, line);
  lineSplit = split(line, '\t');
  for_each(lineSplit.begin(), lineSplit.end(), &removeBrackets );
  set<string> acceptStates = convertToSet(lineSplit);

  set<transitionFunction> transitionFunctions;
  while(getline(NFAFile, line)) {
    vector<string> splitLine = split(line, ' ');
    string state = removeBrackets(splitLine[0].substr(0, splitLine[0].size() - 1));
    string inputSymbol = splitLine[1];
    string finalState = removeBrackets(splitLine[3]);
    transitionFunctions.insert( transitionFunction {state, inputSymbol, finalState} );
  }
  NFA output = NFA(states, alphabet, startState, acceptStates, transitionFunctions);

  return output;
}
