#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "nfa.h"
#include "IntSet.h"
#include "dfa.h"
#include <math.h>
#include "LinkedList.h"

DFA *NFA_to_DFA(NFA *nfa);

DFA *NFA_to_DFA(NFA *nfa) {
	int n = nfa->nstates;
	DFA_State *states = (DFA_State*)malloc(((int)pow(2,n))*sizeof(DFA_State)); /*potential new states*/
	LinkedList list_states = LinkedList_new();

	IntSet *tracker[(int)pow(2,n)]; /*tracker for index of states*/
	for(int i=0; i<n; i++) {
		tracker[i] = IntSet_new();
	}
	int k=1; /*tracker for number of states*/
	IntSet_add(tracker[0], 0);

	for(int i=0; i<k; i++) {
		for(int sym=0; sym<NFA_NSYMBOLS; sym++) {
			IntSet *dst = IntSet_new();
			IntSetIterator *current_s_iterator = IntSet_iterator(tracker[i]);
			while(IntSetIterator_has_next(current_s_iterator)) {
				int tempState = IntSetIterator_next(current_s_iterator);
				IntSet_union(dst, nfa->states[tempState].transitions[sym]);
				
				if(nfa->states[tempState].is_accepting) {
					states[i].is_accepting = TRUE;
					LinkedList_element_at(list_states,i).is_accepting = TRUE;				}
			}

			int equalState = -1;
			for(int t=0; t<k; t++) {
				if(IntSet_equals(dst, tracker[t])) {
					equalState = t;
				}
			}

			if(equalState == -1) {
				IntSet_union(tracker[k], dst);
				states[i].transitions[sym] = k;
				LinkedList_element_at(list_states,i).transitions[sym] = k;
				k++;
			}

			else {
				states[i].transitions[sym] = equalState;
				LinkedList_element_at(list_states,i).transitions[sym] = equalState;
			}
		}
	}


	/*now to create the final dfa*/

	DFA *new_DFA = DFA_new(k);
	for(int i=0; i<k; i++) {
		new_DFA->states[i] = states[i];
	}

	return new_DFA;
}

int main (int argc, char **argv) { 
	return 0;
}