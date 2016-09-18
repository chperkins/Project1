#ifndef _dfa_h
#define _dfa_h

#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "dfa.h"


DFA *DFA_new(int n) {
    DFA *dfa = (DFA*)malloc(sizeof(DFA));
    dfa->nstates = n;
    dfa->current_state = 0;
    dfa->states = (DFA_State*)malloc(n*sizeof(DFA_State));  /* not sure about this statement. Trying to dynamically allocate space */
    for (int i = 0; i < n; i++) {
    	dfa->states[i].is_accepting = FALSE;
    }
    for (int i=0; i<n; i++) {
    	for(int j=0; j<DFA_NSYMBOLS; j++) {
    		dfa->states[i].transitions[j]=DFA_NO_TRANSITION;
    	}
    }
    return dfa;  
}

int DFA_get_size(DFA *dfa) {
	return dfa->nstates;
}

int DFA_get_transition(DFA *dfa, int statenum, char symbol) {
	return dfa->states[statenum].transitions[symbol];  /*don't know how to use pointers*/
	/*states[statenum]*/
}

void DFA_set_transition(DFA *dfa, int src, char symbol, int dst) {
	dfa->states[src].transitions[symbol] = dst;
}

void DFA_set_transition_str(DFA *dfa, int src, char *str, int dst) {
	for(int i=0; str[i] != '\0'; i++) {
		dfa->states[src].transitions[str[i]] = dst;
	}
}

void DFA_set_transition_str(DFA *dfa, int src, char *str, int dst) {
	for(int i=0; i<DFA_NSYMBOLS; i++) {
		dfa->states[src].transitions[i] = dst;
	}
}

int DFA_get_current_state(DFA *dfa) {
    return dfa->current_state;

void DFA_set_current_state(DFA *dfa, int statenum) {
    dfa->current_state = statenum;
}

int DFA_get_accepting(DFA *dfa, int statenum) {
	return dfa->states[statenum].is_accepting;
}

void DFA_set_accepting(DFA *dfa, int statenum, int value) {
	dfa->states[statenum].is_accepting = value;
}



int main (int argc, char **argv) {
	DFA *trial  = DFA_new(3);
	DFA_get_size(trial);
	DFA_set_transition(trial,0,'a',1);
	printf("%d \n", DFA_get_transition(trial, 0, 'a'));
	DFA_set_transition_str(trial,0,"bc",2);
	printf("%d \n", DFA_get_transition(trial, 0, 'b'));
	DFA_set_current_state(trial,2);
	printf("%d",DFA_get_current_state(trial));

} /*synced up*/

#endif
