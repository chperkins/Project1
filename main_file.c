#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "nfa.h"
#include "IntSet.h"
#include "dfa.h"
#include <math.h>
#include "LinkedList.h"

DFA *NFA_to_DFA(NFA *nfa);

DFA_State *DFA_State_new();

DFA_State *DFA_State_new() {
	DFA_State *x = (DFA_State*)malloc(sizeof(DFA_State));
	x->is_accepting = false;
	for(int sym=0; sym<NFA_NSYMBOLS; sym++) {
		x->transitions[sym] = -1;
	}
	return x;
}

DFA *NFA_to_DFA(NFA *nfa) {
	printf("ok1 \n");
	int n = nfa->nstates; //saves number of states in original nfa
	printf("ok2 \n");
	int n_dfa_states = (int)pow(2,n); //saves 2^n
	printf("ok3 \n");
	//DFA_State *states = (DFA_State*)malloc(n_dfa_states*sizeof(DFA_State)); //potential new states
	LinkedList *states1 = LinkedList_new();
	printf("ok4");
	IntSet *tracker[n_dfa_states]; //tracker for index of states, each contains subset of nfa states
	printf("ok5");
	for(int i=0; i<n_dfa_states; i++) {
		tracker[i] = IntSet_new(); //initializes each tracker
	}

	printf("ok6 \n");
	int k= 1; //tracker for number of states
	printf("ok6.5 \n");
	IntSet_add(tracker[0], 0); //sets the first tracker as intset of 0
	printf("ok7 \n");
	DFA_State *state0 = DFA_State_new();
	printf("ok8 \n");
	LinkedList_add_at_end(states1, state0);
	printf("ok9 \n");
	LinkedListIterator *listIterate = LinkedList_iterator(states1);
	printf("ok10 \n");

	int i=0;

	while(LinkedListIterator_has_next(listIterate)) { //goes through each state
		printf("ok %d \n", i);
		for(int sym=0; sym<NFA_NSYMBOLS; sym++) { //goes through each symbol
			printf("t1 \n");
			DFA_State *currentState = DFA_State_new();
			currentState = LinkedListIterator_next(listIterate);
			//printf("%d", currentState->transitions[0]);
			printf("t2 \n");
			IntSet *dst = IntSet_new(); //makes a new intset of destinations given sym on states[i]
			printf("t3 \n");
			IntSetIterator *current_s_iterator = IntSet_iterator(tracker[i]); //creates iterator
			printf("t4 \n");
			while(IntSetIterator_has_next(current_s_iterator)) {
				printf("c1 \n");
				int tempState = IntSetIterator_next(current_s_iterator);
				printf("c2 \n");
				IntSet_union(dst, nfa->states[tempState].transitions[sym]); //unions transitions to the destination
				printf("c3 \n");
				
				if(nfa->states[tempState].is_accepting) {
					printf("d1 \n");
					currentState->is_accepting = TRUE; //if any state in the nfa is accepting, then states[i] should be too
				}
			}
			//now we search to see if dst has already been created
			printf("t5 \n");
			int equalState = -1; //-1 is a default no value
			for(int t=0; t<k; t++) {
				if(IntSet_equals(dst, tracker[t])) {
					equalState = t; //if we found an equal
				}
			}
			printf("t6 \n");
			if(equalState == -1) {
				printf("y1 \n");
				IntSet_union(tracker[k], dst); //this sets tracker k to be dst so that it willb saved and searchable
				printf("y2 \n");
				currentState->transitions[sym] = k; //sets the transition from states[i] to k, the new state
				printf("y3 \n");
				DFA_State *state_k = DFA_State_new();
				printf("y4 \n");
				LinkedList_add_at_end(states1, state_k);
				printf("y5 \n");
				k++;
			}
			else {
				printf("z1 %d \n", equalState);
				currentState->transitions[sym] = equalState; //since dst = equalState, this should be the transition
				printf("z2 \n");
			}
			printf("t7 \n");

			//IntSet_free(dst);
			//free(current_s_iterator);
			//free(currentState);
		}
		i++;
	}


	//now to create the final dfa

	DFA *new_DFA = DFA_new(k); //generates dfa
	for(int l=0; l<k; l++) { //copies over all of the states
		DFA_State *oneState = DFA_State_new();
		oneState = LinkedList_element_at(states1, l);
		new_DFA->states[l] = *oneState;
	}
	for(int l=0; l<n_dfa_states; l++) {
		IntSet_free(tracker[l]);
	}

	return new_DFA;
}

int main (int argc, char **argv) { 

	DFA *trial  = DFA_new(3);
    printf("trial");
	/*DFA *trial  = DFA_new(3);
	DFA_get_size(trial);
	DFA_set_transition(trial,0,'a',1);
	printf("%d \n", DFA_get_transition(trial, 0, 'a'));
	DFA_set_transition_str(trial,0,"bc",2);
	printf("%d \n", DFA_get_transition(trial, 0, 'b'));
	DFA_set_current_state(trial,2);

	printf("%d",DFA_get_current_state(trial));
    
	printf("%d \n",DFA_get_current_state(trial));
    DFA_free(trial);

	DFA *problem_1 = DFA_new(3);
    printf("problem_1 \n");
	DFA_set_transition(problem_1, 0,'a', 1);
	DFA_set_transition(problem_1, 1, 'b', 2);
	DFA_set_accepting(problem_1, 2, TRUE);
    DFA_free(problem_1);

	DFA *problem_2 = DFA_new(3);
    printf("problem_2 \n");
	DFA_set_transition(problem_2, 0,'a', 1);
	DFA_set_transition(problem_2, 1, 'b', 2);
	DFA_set_transition_all(problem_2, 2, 2);
	DFA_set_accepting(problem_2, 2, TRUE);
	printf("%d \n", DFA_execute(problem_2, "ab"));
	printf("%d \n", DFA_execute(problem_2, "abc"));
	printf("%d \n", DFA_execute(problem_2, "xyz"));
	printf("%d \n", DFA_execute(problem_2, "xyzab"));
    DFA_free(problem_2);

	DFA *problem_3 = DFA_new(2);
    printf("problem_3 \n");
	DFA_set_transition_all(problem_3, 0, 0);
	DFA_set_transition_all(problem_3, 1, 1);
	DFA_set_transition(problem_3, 0, '1', 1);
	DFA_set_transition(problem_3, 1, '1', 0);

	DFA_print(problem_3);
	DFA_free(problem_3);*/

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
    printf("%d \n", NFA_execute(p1, "abbbaabababababa"));*/

    /*NFA *p2 = NFA_new(4);
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

    /*NFA *wston = NFA_new(20);
    printf("wston \n");
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

    //printf("%d \n", NFA_execute(wston, "washington"));

    //DFA *dfa_wston = NFA_to_DFA(wston);
    //printf("%d \n", DFA_execute(dfa_wston, "washington"));


    NFA_free(wston);*/

    NFA *problem1 = NFA_new(4);
    printf("problem1 \n");
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
  

    DFA *dfa_test = NFA_to_DFA(problem1);
    printf("dfa_test \n");
    DFA_print(dfa_test);
    printf("DFA STUFF %d \n", DFA_execute(dfa_test, "man"));
    printf("%d \n", DFA_execute(dfa_test, "aewifasdciuandvx"));
    printf("%d \n", DFA_execute(dfa_test, "amanb"));
    printf("%d \n", DFA_execute(dfa_test, "manabc"));
    printf("%d \n", DFA_execute(dfa_test, "defman"));
    DFA_free(dfa_test);
    NFA_free(problem1);


    printf("%d \n", DFA_execute(dfa_test, "manmanman"));
    printf("%d \n", DFA_execute(dfa_test, "manmanman1"));


    //DFA_free(dfa_test);

	return 0;
}