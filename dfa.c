#ifndef _dfa_h
#define _dfa_h

#include <stdbool.h>


DFA *
DFA_new(int n) {
    DFA *dfa = (DFA*)malloc(sizeof(DFA));
    dfa->nstates = n;
    dfa->current_state = 0;
    dfa->states = (DFA_State*)malloc(n*sizeof(DFA_State));  /* not sure about this statement. Trying to dynamically allocate space */
    return dfa;  
}