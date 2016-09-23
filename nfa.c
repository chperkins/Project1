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
        nfa->states[i].is_accepting = FALSE;
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
    for(int i=0; i<NFA_NSYMBOLS; i++) {
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

bool NFA_subExecute(NFA *nfa, IntSet *startStates, char *input) {
    IntSetIterator *current_s_iterator = IntSet_iterator(startStates); /*creates iterator of possible current states*/
    while(IntSetIterator_has_next(current_s_iterator)) { /*condition makes sure the intset isn't empty

        int tempState = IntSetIterator_next(current_s_iterator);
        /*printf("%d %d \n", tempState, input[0]=='\0' && nfa->states[tempState].is_accepting);*/

        /*for when the input string isn't empty, we want to continue running execute depth first*/

        if(input[0] != '\0') {
           bool tempBool = NFA_subExecute(nfa, nfa->states[tempState].transitions[input[0]], (input+1));
           if(tempBool) {
            return TRUE;
           }
        }

        else if(nfa->states[tempState].is_accepting) {
            return TRUE;
        }
    }
    return FALSE;
}

bool NFA_execute(NFA *nfa, char *input) {
    return NFA_subExecute(nfa, nfa->current_states, input);
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



int main (int argc, char **argv) {
    /*NFA *test = NFA_new(5);
    NFA_add_transition(test, 0, 'a', 1);
    IntSet_print(NFA_get_transitions(test, 0, 'a'));*/

    /*NFA *p1 = NFA_new(3);
    NFA_add_transition(p1, 0, 'a', 1);
    NFA_add_transition(p1, 1, 'b', 2);
    NFA_set_accepting(p1, 2, TRUE);
    printf("%d \n", NFA_execute(p1, ""));
    printf("%d \n", NFA_execute(p1, "a"));
    printf("%d \n", NFA_execute(p1, "ab"));
    printf("%d \n", NFA_execute(p1, "abc"));
    printf("%d \n", NFA_execute(p1, "def"));*/

    NFA *problem1 = NFA_new(4);
    NFA_add_transition(problem1, 0,'m',1);
    NFA_add_transition(problem1, 1,'a',2);
    NFA_add_transition(problem1, 2,'n',3);
    NFA_add_transition_all(problem1, 0,0);
    NFA_set_accepting(problem1, 3, TRUE);
    printf("%d \n", NFA_execute(problem1, "man"));
    printf("%d \n", NFA_execute(problem1, "aewifasdciuandvx"));
    printf("%d \n", NFA_execute(problem1, "amanb"));
    printf("%d \n", NFA_execute(problem1, "manabc"));
    printf("%d \n", NFA_execute(problem1, "defman"));

    return 0;
}


#endif
