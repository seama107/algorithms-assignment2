#include "transitionFunction.h"

using namespace std;

ostream& operator<<(ostream& out, const transitionFunction& t)
{
  out << t.state << ", " << t.input << " = " << t.finalState;

  return out;
}
