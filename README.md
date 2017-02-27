# Algorithms Assignment 2

**Author:** Michael Seaman

**Due date:** 2/28/16, 11:30 AM

---

## Setup:

Compile : `make`.
Run : `./DFAtranslator <NFA_FILENAME>`

### Known Bugs:

* In rare occasions, duplicate transition functions will be outputted.

## Programming Assignment

Write a C++ or Java program that takes the specification for a
NFA as input and outputs the specification for an equivalent DFA. The
NFA input specification will be passed as a command line argument
and be of the following form:
* Line 1: A list of states, Q, separated by tabs.
* Line 2: A list of the symbols in Σ, separated by tabs. The string E will not be explicitly included.
* Line 3: The start state, q0 ∈ Q.
* Line 4: The set of accept states, F, separated by tabs.
* Line 5 to EOF: The transition function.
Each line will be of the form s, x = sf. This is translated to mean
that reading symbol x in state s causes a transition to state sf.
The string EPS will be used to represent an epsilon transition.
The output should be to a text file with the extension .DFA. The
output should have the same format as above. You may use the symbol
EM to represent the empty state, ∅. If {1} and {2} are states in the
NFA that are combined in the DFA, represent the state with the string
{1,2}.
Grading will be based on correctness and elegance of solution. Make
sure to develop an OO solution. Comment your code. You should
provide a Makefile as well.

## Submission Instructions

Create a zip file named <yourname>assign2.zip which includes your
source code, a Makefile, and a README. The README should contain
any comments you have about the assignment, as well as the command
to run your program. Submit the zip file to Blackboard by the
deadline above. Remember that no late work will be accepted. Be
prepared to demo in class on sample inputs provided by the instructor.

---
## Honor Pledge

I pledge that all the work in this repository besides the following citations is my own!

- Splitting a string into a vector, code used from Evan Teran on Stack Exchange:

http://stackoverflow.com/questions/236129/split-a-string-in-c

Signed,

Michael Seaman
