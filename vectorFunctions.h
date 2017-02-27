#ifndef vectorFunctions_h
#define vectorFunctions_h

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>


std::vector<std::string> split(const std::string &s, char delim);

template<typename T>
void split(const std::string &s, char delim, T result) {
  //Splits a string by delim into an iterable T
  //Borrowed from Evan Teran on SE
  std::stringstream ss;
  ss.str(s);
  std::string item;
  while( getline(ss, item, delim)) {
    *(result++) = item;
  }
}

template<typename T>
std::set<T> convertToSet(std::vector<T> input) {
  std::set<T> s (input.begin(), input.end());
  return s;
}

template<typename T, typename U>
std::set<T> subsetWhereEquals(std::set<T> s, U condition) {
  //Returns a subset of s where each element == condition
  std::set<T> subset = {};
  for(T elem : s) {
    if(elem == condition) {
      subset.insert(elem);
    }
  }
  return subset;
}

template<typename T, typename U>
std::set<T> setIntersect(std::set<T> set1,std::set<U> set2) {
  std::set<T> subset = {};
  for(U condition : set2) {
    std::set<T> validMembers = subsetWhereEquals(set1, condition);
    subset.insert(validMembers.begin(), validMembers.end());
  }
  return subset;
}


#endif
