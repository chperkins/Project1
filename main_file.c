#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "nfa.h"
#include "IntSet.h"
#include "dfa.h"
#include <math.h>

DFA *NFA_to_DFA(NFA *nfa);

DFA *NFA_to_DFA(NFA *nfa) {
	int n = nfa->nstates;
	DFA_State *states = (DFA_State*)malloc(((int)pow(2,n))*sizeof(DFA_State)); /*potential new states*/
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
				}
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
				k++;
			}

			else {
				states[i].transitions[sym] = equalState;
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

	DFA *trial  = DFA_new(3);
	DFA_get_size(trial);
	DFA_set_transition(trial,0,'a',1);
	printf("%d \n", DFA_get_transition(trial, 0, 'a'));
	DFA_set_transition_str(trial,0,"bc",2);
	printf("%d \n", DFA_get_transition(trial, 0, 'b'));
	DFA_set_current_state(trial,2);

	printf("%d",DFA_get_current_state(trial));
    
	printf("%d \n",DFA_get_current_state(trial));

	DFA *problem_1 = DFA_new(3);
	DFA_set_transition(problem_1, 0,'a', 1);
	DFA_set_transition(problem_1, 1, 'b', 2);
	DFA_set_accepting(problem_1, 2, TRUE);

	DFA *problem_2 = DFA_new(3);
	DFA_set_transition(problem_2, 0,'a', 1);
	DFA_set_transition(problem_2, 1, 'b', 2);
	DFA_set_transition_all(problem_2, 2, 2);
	DFA_set_accepting(problem_2, 2, TRUE);
	printf("%d \n", DFA_execute(problem_2, "ab"));
	printf("%d \n", DFA_execute(problem_2, "abc"));
	printf("%d \n", DFA_execute(problem_2, "xyz"));
	printf("%d \n", DFA_execute(problem_2, "xyzab"));

	DFA *problem_3 = DFA_new(2);
	DFA_set_transition_all(problem_3, 0, 0);
	DFA_set_transition_all(problem_3, 1, 1);
	DFA_set_transition(problem_3, 0, '1', 1);
	DFA_set_transition(problem_3, 1, '1', 0);

	DFA_print(problem_3);
	DFA_free(problem_3);



	   /*NFA *test = NFA_new(5);
    NFA_add_transition(test, 0, 'a', 1);
    IntSet_print(NFA_get_transitions(test, 0, 'a'));*/

    /*NFA *p1 = NFA_new(2);
    NFA_add_transition_str(p1, 0, "ab", 0);
    NFA_add_transition_str(p1, 0, "ab", 1);
    NFA_add_transition_str(p1, 1, "ab", 1);
    NFA_set_accepting(p1, 1, TRUE);
    NFA_set_accepting(p1, 0, TRUE);
    printf("%d \n", NFA_execute(p1, ""));
    printf("%d \n", NFA_execute(p1, "a"));
    printf("%d \n", NFA_execute(p1, "ab"));
    printf("%d \n", NFA_execute(p1, "abc"));
    printf("%d \n", NFA_execute(p1, "def"));
    printf("%d \n", NFA_execute(p1, "abbbaabababababa"));

    NFA *p2 = NFA_new(4);
    NFA_add_transition_str(p2, 0, "abc", 0);
    NFA_add_transition_str(p2, 3, "abc", 3);
    NFA_add_transition(p2, 0, 'a', 1);
    NFA_add_transition(p2, 1, 'b', 2);
    NFA_add_transition(p2, 2, 'c', 3);
    NFA_set_accepting(p2, 3, TRUE);
    printf("%d \n", NFA_execute(p2, ""));
    printf("%d \n", NFA_execute(p2, "abbbb"));
    printf("%d \n", NFA_execute(p2, "01abc01"));
    printf("%d \n", NFA_execute(p2, "cccabcaaa"));
    printf("%d \n", NFA_execute(p2, "abcabcabcabcabc"));
    NFA_free(p2);*/

    NFA *wston = NFA_new(20);
    NFA_add_transition_all(wston, 0, 0);

    NFA_add_transition(wston, 0, 'a', 1);
    NFA_add_transition_all(wston, 1, 1);
    NFA_add_transition(wston, 1, 'a', 2);
    NFA_add_transition_all(wston, 2, 2);

    NFA_add_transition(wston, 0, 'g', 3);
    NFA_add_transition_all(wston, 3, 3);
    NFA_add_transition(wston, 3, 'g', 4);
    NFA_add_transition_all(wston, 4, 4);

    NFA_add_transition(wston, 0, 'h', 5);
    NFA_add_transition_all(wston, 5, 5);
    NFA_add_transition(wston, 5, 'h', 6);
    NFA_add_transition_all(wston, 6, 6);

    NFA_add_transition(wston, 0, 'i', 7);
    NFA_add_transition_all(wston, 7, 7);
    NFA_add_transition(wston, 7, 'i', 8);
    NFA_add_transition_all(wston, 8, 8);

    NFA_add_transition(wston, 0, 'n', 9);
    NFA_add_transition_all(wston, 9, 9);
    NFA_add_transition(wston, 9, 'n', 10);
    NFA_add_transition_all(wston, 10, 10);
    NFA_add_transition(wston, 10, 'n', 11);
    NFA_add_transition_all(wston, 11, 11);

    NFA_add_transition(wston, 0, 'o', 12);
    NFA_add_transition_all(wston, 12, 12);
    NFA_add_transition(wston, 12, 'o', 13);
    NFA_add_transition_all(wston, 13, 13);

    NFA_add_transition(wston, 0, 's', 14);
    NFA_add_transition_all(wston, 14, 14);
    NFA_add_transition(wston, 14, 's', 15);
    NFA_add_transition_all(wston, 15, 15);

    NFA_add_transition(wston, 0, 't', 16);
    NFA_add_transition_all(wston, 16, 16);
    NFA_add_transition(wston, 16, 't', 17);
    NFA_add_transition_all(wston, 17, 17);

    NFA_add_transition(wston, 0, 'w', 18);
    NFA_add_transition_all(wston, 18, 18);
    NFA_add_transition(wston, 18, 'w', 19);
    NFA_add_transition_all(wston, 19, 19);

    NFA_set_accepting(wston, 2, TRUE);
    NFA_set_accepting(wston, 4, TRUE);
    NFA_set_accepting(wston, 6, TRUE);
    NFA_set_accepting(wston, 8, TRUE);
    NFA_set_accepting(wston, 11, TRUE);
    NFA_set_accepting(wston, 13, TRUE);
    NFA_set_accepting(wston, 15, TRUE);
    NFA_set_accepting(wston, 17, TRUE);
    NFA_set_accepting(wston, 19, TRUE);

    printf("%d \n", NFA_execute(wston, "washington"));

    /*NFA *problem1 = NFA_new(4);
    NFA_add_transition(problem1, 0,'m',1);
    NFA_add_transition(problem1, 1,'a',2);
    NFA_add_transition(problem1, 2,'n',3);
    NFA_add_transition_all(problem1, 0,0);
    NFA_set_accepting(problem1, 3, TRUE);
    printf("%d \n", NFA_execute(problem1, "man"));
    printf("%d \n", NFA_execute(problem1, "aewifasdciuandvx"));
    printf("%d \n", NFA_execute(problem1, "amanb"));
    printf("%d \n", NFA_execute(problem1, "manabc"));
    printf("%d \n", NFA_execute(problem1, "defman"));*/

	return 0;
}