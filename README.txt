CSC 173
Project 1: Finite Automata
Collaborators: Charlie Perkins, Le Xuan Luba, Maria Weber

Compile/Run Instructions:
- In command line, navigate to project folder
- Use command "make", which will compile and execute the program

Clean:
- Use "make clean" to remove executable

Reading Output: 
The output of this program is divided by problem and part of each problem, with a one sentence description of the goal. 
For each DFA problem the program prints the DFA, followed by several test cases and their result. 
For each NFA the program will print test cases, and then the converted NFA -> DFA (in problem 3).

For each state i the program prints the transitions for a given input in the form: State i: | 'trans_char', dest_state |

Example Output:
- State 0: |'a',1| |'b', 2| |'c', 0|
This means on state 0 we transition to state 1 given character 'a', to state 2 given character 'b', and to state 0 given character 'c'.
- State 0: |all - 'z', 1|
This means on state 0 any given input except for 'z' will transition to state 1. 

Test for "test_string": Where test_string is a string being checked for validity with the language. Returns 1 for TRUE (ended in accepting state) or 0 for FALSE (invalid for given automata).

Note on Problem 3: 
The NFA->DFA conversion for the NFA specified in Problem 2 (b) was commented out because it had too many states to have a reasonable run time. We believe that the conversion runs correctly, just that the problem is too big to be worth converting.