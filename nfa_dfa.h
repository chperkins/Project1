
#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "nfa.h"
#include "IntSet.h"

extern DFA *NFA_to_DFA(NFA *nfa);

extern DFA_State *DFA_State_new();