#ifndef _dfa_h
#define _dfa_h

#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "dfa.h"


DFA *DFA_new(int n) {
    DFA *dfa = (DFA*)malloc(sizeof(DFA)); /*frees space for the dfa*/
    dfa->nstates = n;
    dfa->current_state = 0;
    dfa->states = (DFA_State*)malloc(n*sizeof(DFA_State)); /*frees space for the states*/
    for(int i=0; i<n; i++) {
    	dfa->states[i].is_accepting = FALSE;
    } /*initializes all accepting values as false*/
    for (int i=0; i<n; i++) {
    	for(int j=0; j<DFA_NSYMBOLS; j++) {
    		dfa->states[i].transitions[j]=DFA_NO_TRANSITION;
    	}
    } /*makes default transitions as no transitions*/
    return dfa;  
}

int DFA_get_size(DFA *dfa) {
	return dfa->nstates;
}

int DFA_get_transition(DFA *dfa, int statenum, char symbol) {
	return dfa->states[statenum].transitions[symbol]; 
	/*receives transition for the state[statenum] when we input symbol. Indexed by symbols*/
}

void DFA_set_transition(DFA *dfa, int src, char symbol, int dst) {
	dfa->states[src].transitions[symbol] = dst;
	/*sets the transitions for states[src] on symbol to be dst*/
}

void DFA_set_transition_str(DFA *dfa, int src, char *str, int dst) {
	for(int i=0; str[i] != '\0'; i++) {
		dfa->states[src].transitions[str[i]] = dst;
	}
	/*sets transition for each member of the string*/
}

void DFA_set_transition_all(DFA *dfa, int src, int dst) {
	for(int i=0; i<DFA_NSYMBOLS; i++) {
		dfa->states[src].transitions[i] = dst;
	}

	/*sets the same transition for all symbols*/
}

int DFA_get_current_state(DFA *dfa) {
    return dfa->current_state;
}

void DFA_set_current_state(DFA *dfa, int statenum) {
    dfa->current_state = statenum;
}

int DFA_get_accepting(DFA *dfa, int statenum) {
	return dfa->states[statenum].is_accepting;
}

void DFA_set_accepting(DFA *dfa, int statenum, int value) {
	dfa->states[statenum].is_accepting = value;
}

int DFA_execute(DFA *dfa, char *input) {
	for(int i=0; input[i] != '\0'; i++) {
		dfa->current_state = dfa->states[dfa->current_state].transitions[input[i]];
		if(dfa->current_state == -1) {
			return FALSE;
		}
	} /* sets the current state to the transition of the previous state over and over*/
	return dfa->states[dfa->current_state].is_accepting; /*returns accepting value of the final state*/
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

	DFA *problem_1 = DFA_new(3);
	DFA_set_transition(problem_1,'a', 1);
	DFA_set_transition(problem_1, 'b', 2);
	DFA_set_accepting(problem_1, 2, TRUE);
	DFA_execute(problem_1, "ab");

} /*synced up*/

#endif
