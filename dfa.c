#ifndef _dfa_h
#define _dfa_h

#include <stdbool.h>


DFA *DFA_new(int n) {
    DFA *dfa = (DFA*)malloc(sizeof(DFA));
    dfa->nstates = n;
    dfa->current_state = 0;
    dfa->states = (DFA_State*)malloc(n*sizeof(DFA_State));  /* not sure about this statement. Trying to dynamically allocate space */
    return dfa;  
}

int DFA_get_size(DFA *dfa) {
	return dfa->nstates;
}

int DFA_get_transition(DFA *dfa, int statenum, char symbol) {
	return *dfa->(*(states + statenum))->transitions[symbol];  /*don't know how to use pointers*/
	/*states[statenum]*/
}

void DFA_set_transition(DFA *dfa, int src, char symbol, int dst) {
	*dfa->(*(states + statenum))->transitions[symbol] = dst;
}

