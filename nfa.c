#ifndef _nfa_h
#define _nfa_h

#include <stdio.h> \
#include <stdbool.h>
#include "nfa.h"
#include "IntSet.h"

NFA *NFA_new(int n) {
    NFA *nfa = (NFA*)malloc(sizeof(NFA));
    nfa->nstates = n;
    IntSet *start = IntSet_New();
    IntSet_add(start, 0);
    nfa->current_states = start;
    nfa->states = (NFA_State*)malloc(n*sizeof(NFA_State));  /* not sure about this statement. Trying to dynamically allocate space */
    return nfa;
}

int NFA_get_size(NFA *nfa) {
	return nfa->nstates;
}

IntSet *NFA_get_transitions(NFA *nfa, int statenum, char symbol) {
	return nfa->states[statenum]->transitions[symbol];
}
