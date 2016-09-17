#ifndef _nfa_h
#define _nfa_h

#include <stdio.h> \
#include <stdbool.h>
#include "nfa.h"

NFA *NFA_new(int n) {
    DFA *dfa = (DFA*)malloc(sizeof(DFA));
    dfa->nstates = n;
    dfa->current_state = 0;
    dfa->states = (DFA_State*)malloc(n*sizeof(DFA_State));  /* not sure about this statement. Trying to dynamically allocate space */
    return dfa;  
}
