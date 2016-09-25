#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "nfa.h"
#include "IntSet.h"
#include "dfa.h"
#include <math.h>
#include "LinkedList.h"
#include "nfa_dfa.h"

DFA_State *DFA_State_new() {
	DFA_State *x = (DFA_State*)malloc(sizeof(DFA_State));
	x->is_accepting = FALSE;
	for(int sym=0; sym<NFA_NSYMBOLS; sym++) {
		x->transitions[sym] = -1;
	}
	return x;
}

DFA *NFA_to_DFA(NFA *nfa) {
	//printf("ok1 \n");
	LinkedList *states = LinkedList_new(); //creates new linked list for states
	LinkedList *intsets = LinkedList_new(); //creates corresponding linked list for the intsets of the nfa state corresponding to dfa state
	//printf("ok2 \n");

	DFA_State *state0 = DFA_State_new();
	LinkedList_add_at_end(states, state0); //adds a first initial state 0 to the linked list of dfa states
	IntSet *first_IS = IntSet_new();
	IntSet_add(first_IS, 0);
	LinkedList_add_at_end(intsets, first_IS);
	//printf("ok3 \n");

	int num_states=1;
	LinkedListIterator *listIterate = LinkedList_iterator(states); //creates iterator for dfa states
	LinkedListIterator *isIterate = LinkedList_iterator(intsets); //creates iterator for intsets of nfa states

	while(LinkedListIterator_has_next(listIterate)) { //checks if there is another dfa states
		//printf("%d number of states \n", num_states);
		DFA_State *currentState = LinkedListIterator_value(listIterate); //takes current value but doesn't iterate
		IntSet *currentIS = LinkedListIterator_value(isIterate);
		for(int sym=0; sym<NFA_NSYMBOLS; sym++) { //goes through each symbol
			IntSet *dst = IntSet_new(); //creates an intset to gather all destinations on sym
			IntSetIterator *current_s_iterator = IntSet_iterator(currentIS); //iterates through each current state of nfa
			while(IntSetIterator_has_next(current_s_iterator)) { //checks for another state in nfa
				int tempState = IntSetIterator_next(current_s_iterator);
				IntSet_union(dst, nfa->states[tempState].transitions[sym]); //unions destinations to dst

				if(nfa->states[tempState].is_accepting) {
					currentState->is_accepting = TRUE; //if any state in the nfa is accepting, then states[i] should be too
				}
			}
			free(current_s_iterator);

			//printf("%c", sym);
			//IntSet_print(dst);

			int containInt = -1; //tracks whether dst is new or not
			int iterint = 0;
			LinkedListIterator *tempIterate = LinkedList_iterator(intsets);
			while(LinkedListIterator_has_next(tempIterate)) {
				IntSet *tempIntSet = LinkedListIterator_next(tempIterate);
				if(IntSet_equals(tempIntSet, dst)) {
					containInt=iterint;
				} //this is required since linked_list_contains doesn't work the same
				iterint++;
			}
			free(tempIterate);

			//printf("if %d %d satisfied? \n", !IntSet_is_empty(dst), containInt == -1);

			if(containInt < 0 && (!(IntSet_is_empty(dst)))) {
				//printf("ok i got here \n");
				DFA_State *state_k = DFA_State_new();
				currentState->transitions[sym]=num_states;
				//printf("transition to %d on %c \n", num_states, sym);
				LinkedList_add_at_end(states, state_k);
				LinkedList_add_at_end(intsets, dst);
				num_states+=1;
			}//if dst is new, we add it as a new dfa state

			else if(!(IntSet_is_empty(dst))) {
				currentState->transitions[sym]=containInt;
			}//if not, we just set the current state to have the old state as a transition
		}
		DFA_State *nextState = LinkedListIterator_next(listIterate);
		IntSet *next = LinkedListIterator_next(isIterate); //iterates through stuff
	}

	DFA *new_DFA = DFA_new(num_states); //generates dfa
	LinkedListIterator *finalStates = LinkedList_iterator(states);
	for(int l=0; l<num_states; l++) { //copies over all of the states
		DFA_State *oneState = LinkedListIterator_next(finalStates);
		new_DFA->states[l] = *oneState;
		free(oneState);
	}

	free(finalStates); //frees stuff
	free(listIterate);
	free(isIterate);
	return new_DFA;
}