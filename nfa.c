#ifndef _nfa_h
#define _nfa_h

#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "nfa.h"
#include "IntSet.h"

NFA *NFA_new(int n) {
    NFA *nfa = (NFA*)malloc(sizeof(NFA));
    nfa->nstates = n;
    IntSet *start = IntSet_new();
    IntSet_add(start, 0);
    nfa->current_states = start;
    nfa->states = (NFA_State*)malloc(n*sizeof(NFA_State));
    for(int i=0; i<n; i++) {
        for(int j=0; j<NFA_NSYMBOLS; j++) {
            nfa->states[i].transitions[j] = IntSet_new();
        }
        nfa->states[i].is_accepting = 0;
    } /*initializes all accepting values as false*/
    return nfa;
}

int NFA_get_size(NFA *nfa) {
	return nfa->nstates;
}

IntSet *NFA_get_transitions(NFA *nfa, int statenum, char symbol) {
	return nfa->states[statenum].transitions[symbol];
}

void NFA_add_transition(NFA *nfa, int src, char symbol, int dst) {
    IntSet_add(nfa->states[src].transitions[symbol], dst);
}

void NFA_add_transition_str(NFA *nfa, int src, char *str, int dst) {
    for(int i=0; str[i] != '\0'; i++) {
        IntSet_add(nfa->states[src].transitions[str[i]], dst);
    }
}

void NFA_add_transition_all(NFA *nfa, int src, int dst) {
    for(int i=0; i<=NFA_NSYMBOLS; i++) {
        IntSet_add(nfa->states[src].transitions[i], dst);
    }
}

IntSet *NFA_get_current_states(NFA *nfa) {
    return nfa->current_states;
}

void NFA_set_current_states(NFA *nfa, IntSet *states) {
    nfa->current_states = states;
}

void NFA_set_current_state(NFA *nfa, int state) {
    IntSet *current = IntSet_new();
    IntSet_add(current, state);
    nfa->current_states = current;
}

bool NFA_get_accepting(NFA *nfa, int statenum) {
    return nfa->states[statenum].is_accepting;
}

void NFA_set_accepting(NFA *nfa, int statenum, bool value) {
    nfa->states[statenum].is_accepting = value; /*will this modify the is_accepting? do i need to point to the value or is this just fine?*/
}


void NFA_free(NFA *nfa) {
    for (int i = 0; i < nfa->nstates; i++) {
        NFA_State *state = &nfa->states[i];
        for (int k = 0; k < NFA_NSYMBOLS; k++) {
            IntSet_free(state->transitions[k]);
        }
        free(state->transitions);
        free(state);
    }
    free(nfa);
}


bool NFA_execute(NFA *nfa, char *input) {
    for(int i = 0; input[i] != '\0'; i++) {
        /*set destination to be the set off all states we go to with input[i] from current states*/
        IntSet *destination = IntSet_New();
        /*we use current_s_iterator to iterate through each state in the current states*/
        IntSetIterator *current_s_iterator = IntSet_iterator(nfa->current_states);
        while(IntSetIterator_has_next(current_s_iterator)) { /*this checks if theres another current state*/
            int tempState = current_s_iterator->node->value; /*temp state is the current state to look at*/
            IntSet_union(destination, nfa->states[tempState].transitions[input[i]]); /*this adds all the transitions form tempstate give input to destination*/
            IntSetIterator_next(current_s_iterator); /*this iterates the while loop*/
        }
        nfa->current_states = destination; /*this sets the current state to the set of destination states*/
    } /*we run this over and over again for each input symbol*/

    /*now we have to find out whether we will accept or not*/

    IntSetIterator *final_s_iterator = IntSet_iterator(nfa->current_states); /*create another iterator for the set of last states*/
    while(IntSetIterator_has_next(final_s_iterator)) {
        int tempState = final_s_iterator->node->value;
        /*if the current state is accepting, return true*/
        if(nfa->states[tempState].is_accepting == TRUE) {
            return TRUE;
        }
    }
    /*if nothing accepted, return false*/
    return FALSE;
} 

int main (int argc, char **argv) {
    NFA *test = NFA_new(5);
    NFA_add_transition(test, 0, 'a', 1);
    IntSet_print(NFA_get_transitions(test, 0, 'a'));
    return 0;
}


#endif
