#ifndef transitionFunction_h
#define transitionFunction_h

#include <string>
#include <iostream>

struct transitionFunction
{
  std::string state;
  std::string input;
  std::string finalState;

  friend std::ostream& operator<<(std::ostream& out, const transitionFunction&);

};

//There's some voodoo going on here that I have pieced together. These operators need
//be defined in order to insert into std::set, as each .insert() checks for equality against
//every member in order to be inserted. However, this draws upon a successive operator<
// and operator> instead of operator== for some reason. So, the below operators use ||
// instead of && to make the conditions for 'equality' more stringent.

static bool operator<(const transitionFunction& t1, const transitionFunction& t2) {
  return (t1.state < t2.state) || (t1.input < t2.input) || (t1.finalState < t2.finalState) ;
}

static bool operator>(const transitionFunction& t1, const transitionFunction& t2) {
  return (t1.state > t2.state) || (t1.input > t2.input) || (t1.finalState > t2.finalState) ;
}

static bool operator==(const transitionFunction& t1, const transitionFunction& t2) {
  bool stateEquality = (t1.state == t2.state) || (t1.state == "*") || (t2.state == "*");
  bool inputEquality = (t1.input == t2.input) || (t1.input == "*") || (t2.input == "*");
  bool finalStateEquality = (t1.finalState == t2.finalState) || (t1.finalState == "*") || (t2.finalState == "*");

  return stateEquality && inputEquality && finalStateEquality;
}


#endif
