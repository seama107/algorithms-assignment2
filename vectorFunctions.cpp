#include "vectorFunctions.h"

using namespace std;

vector<string> split(const string &s, char delim) {
  //Vector version of the template function split() in vectorFunctions.h
  vector<string> elems;
  split(s, delim, back_inserter(elems));
  return elems;
}
