#ifndef _nfa_h
#define _nfa_h

#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "nfa.h"
#include "IntSet.h"

NFA *NFA_new(int n) {
    NFA *nfa = (NFA*)malloc(sizeof(NFA)); /*allocates space for nfa*/
    nfa->nstates = n; /*sets size of states to n*/
    IntSet *start = IntSet_new(); /*initializes intset for current states*/
    IntSet_add(start, 0); /*adds 0 to start states*/
    nfa->current_states = start; /*sets current states to start*/
    nfa->states = (NFA_State*)malloc(n*sizeof(NFA_State)); /*allocates spaces for each nfa state*/
    for(int i=0; i<n; i++) { /*iterates over each state*/
        for(int j=0; j<NFA_NSYMBOLS; j++) { /*iterates over each symbol*/
            nfa->states[i].transitions[j] = IntSet_new(); /*initializes each transitions intset*/
        }
        nfa->states[i].is_accepting = FALSE; /*sets default accepting value to false*/
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
    IntSet_add(nfa->states[src].transitions[symbol], dst); /*adds transition to the intset transistions*/
}

void NFA_add_transition_str(NFA *nfa, int src, char *str, int dst) {
    for(int i=0; str[i] != '\0'; i++) { /*iterates over string*/
        IntSet_add(nfa->states[src].transitions[str[i]], dst); /*adds each transition for each char*/
    }
}

void NFA_add_transition_all(NFA *nfa, int src, int dst) {
    for(int i=0; i<NFA_NSYMBOLS; i++) {
        IntSet_add(nfa->states[src].transitions[i], dst); /*adds transition for all symbols*/
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
    IntSet_add(current, state); /*adds tthe desired states to current*/
    nfa->current_states = current; /*sets current states to current intset*/
}

bool NFA_get_accepting(NFA *nfa, int statenum) {
    return nfa->states[statenum].is_accepting;
}

void NFA_set_accepting(NFA *nfa, int statenum, bool value) {
    nfa->states[statenum].is_accepting = value; /*will this modify the is_accepting? do i need to point to the value or is this just fine?*/
}


//TODO 
void NFA_free(NFA *nfa) {
    /*go through array of nfa states*/
    for (int i = 0; i < nfa->nstates; i++) {
        NFA_State *state = &nfa->states[i];
        /*for each state free transition to IntSet on each character*/
        for (int k = 0; k < NFA_NSYMBOLS; k++) {
            IntSet_free(state->transitions[k]);
        }
        /*free the array of transitions*/
        free(state->transitions);
        free(state);
        }
    }


bool NFA_subExecute(NFA *nfa, IntSet *startStates, char *input) {
    IntSetIterator *current_s_iterator = IntSet_iterator(startStates); /*creates iterator of possible current states*/
    while(IntSetIterator_has_next(current_s_iterator)) { /*condition makes sure the intset isn't empty*/
        int tempState = IntSetIterator_next(current_s_iterator);
        /*printf("%d %d \n", tempState, input[0]=='\0' && nfa->states[tempState].is_accepting);*/
        /*for when the input string isn't empty, we want to continue running execute depth first*/
        if(input[0] != '\0') {
            /*recursively calls NFA_subExectue with one less input and setting the current analyzed states as the destinations on tempState
            given input[0]. We call with one elss input to remove the one already used*/
           bool tempBool = NFA_subExecute(nfa, nfa->states[tempState].transitions[input[0]], (input+1));
           /*we save this boolean and return true if true. otherwise we continue*/
           if(tempBool) {
            return TRUE;
           }
        }
        /*if the input is finished and the tempState is accepting, we return true, otherwise we continue with the next state
        in all possible current states*/
        else if(nfa->states[tempState].is_accepting) {
            return TRUE;
        }
    }
    /*if nothing returned true previously and all paths have been searched given the input, we return false*/
    return FALSE;
}


bool NFA_execute(NFA *nfa, char *input) {
    for(int i = 0; input[i] != '\0'; i++) {
        /*set destination to be the set off all states we go to with input[i] from current states*/
        IntSet *destination = IntSet_New();
        /*we use current_s_iterator to iterate through each state in the current states*/
        IntSetIterator *current_s_iterator = IntSet_iterator(nfa->current_states);
        while(IntSetIterator_has_next(current_s_iterator)) { 
        /*this checks if theres another current state*/
            int tempState = current_s_iterator->node->value; 
        /*temp state is the current state to look at*/
            IntSet_union(destination, nfa->states[tempState].transitions[input[i]]); 
            /*this adds all the transitions form tempstate give input to destination*/
            IntSetIterator_next(current_s_iterator); /*this iterates the while loop*/
        }
        nfa->current_states = destination; 
        /*this sets the current state to the set of destination states*/
    } /*we run this over and over again for each input symbol*/
    /*this runs the subExecute function with the first state as the nfa->current states, which should be 0 at the beginning*/
    return NFA_subExecute(nfa, nfa->current_states, input);
}



void NFA_free(NFA *nfa) {
    for (int i = 0; i < nfa->nstates; i++) {
        NFA_State *state = &nfa->states[i]; 
        for (int k = 0; k < NFA_NSYMBOLS; k++) {
            IntSet_free(state->transitions[k]); /*frees each transition[sym] given a state*/
        }
    }
    IntSet_free(nfa->current_states);
    free(nfa->states);
    free(nfa); /*then frees the whole nfa*/
}



int main (int argc, char **argv) {
char [] input;
int index;

}


#endif
