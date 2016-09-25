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
	LinkedListIterator *listIterate = LinkedList_iterator(states);
	LinkedListIterator *isIterate = LinkedList_iterator(intsets);

	while(LinkedListIterator_has_next(listIterate)) {
		//printf("%d number of states \n", num_states);
		DFA_State *currentState = LinkedListIterator_value(listIterate);
		IntSet *currentIS = LinkedListIterator_value(isIterate);
		for(int sym=0; sym<NFA_NSYMBOLS; sym++) {
			IntSet *dst = IntSet_new();
			IntSetIterator *current_s_iterator = IntSet_iterator(currentIS);
			while(IntSetIterator_has_next(current_s_iterator)) {
				int tempState = IntSetIterator_next(current_s_iterator);
				IntSet_union(dst, nfa->states[tempState].transitions[sym]);

				if(nfa->states[tempState].is_accepting) {
					currentState->is_accepting = TRUE; //if any state in the nfa is accepting, then states[i] should be too
				}
			}
			free(current_s_iterator);

			//printf("%c", sym);
			//IntSet_print(dst);

			int containInt = -1;
			int iterint = 0;
			LinkedListIterator *tempIterate = LinkedList_iterator(intsets);
			while(LinkedListIterator_has_next(tempIterate)) {
				IntSet *tempIntSet = LinkedListIterator_next(tempIterate);
				if(IntSet_equals(tempIntSet, dst)) {
					containInt=iterint;
				}
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
			}

			else if(!(IntSet_is_empty(dst))) {
				currentState->transitions[sym]=containInt;
			}
		}
		DFA_State *nextState = LinkedListIterator_next(listIterate);
		IntSet *next = LinkedListIterator_next(isIterate);
	}

	DFA *new_DFA = DFA_new(num_states); //generates dfa
	LinkedListIterator *finalStates = LinkedList_iterator(states);
	for(int l=0; l<num_states; l++) { //copies over all of the states
		DFA_State *oneState = LinkedListIterator_next(finalStates);
		new_DFA->states[l] = *oneState;
		free(oneState);
	}

	free(finalStates);
	free(listIterate);
	free(isIterate);
	return new_DFA;
}

int main (int argc, char **argv) {

	printf("-----------------------------PROBLEM 1----------------------------- \n"); 

	printf("Problem 1 (a) \n");
	DFA *problem1_a = DFA_new(3);
	DFA_set_transition(problem1_a, 0, 'a', 1);
	DFA_set_transition(problem1_a, 1, 'b', 2);
	DFA_set_accepting(problem1_a, 2, TRUE);
    DFA_print(problem1_a);

	printf("\n Problem 1 (b) \n");
	DFA *problem1_b = DFA_new(3);
	DFA_set_transition(problem1_b, 0, 'a', 1);
	DFA_set_transition(problem1_b, 1, 'b', 2);
	DFA_set_transition_all(problem1_b, 2, 2);
	DFA_set_accepting(problem1_b, 2, TRUE);
    DFA_print(problem1_b);

	printf("\n Problem 1 (c) \n");
	DFA *problem1_c = DFA_new(2);
	DFA_set_transition(problem1_c, 0, '1', 1);
	DFA_set_transition(problem1_c, 1, '1', 0);
	DFA_set_transition(problem1_c, 0, '0', 0);
	DFA_set_transition(problem1_c, 1, '0', 1);
	DFA_set_accepting(problem1_c, 0, TRUE);
    DFA_print(problem1_c);

	printf("\n Problem 1 (d) \n");
	DFA *problem1_d = DFA_new(4);
	DFA_set_transition(problem1_d, 0, '1', 1);
	DFA_set_transition(problem1_d, 0, '0', 2);
	DFA_set_transition(problem1_d, 1, '1', 0);
	DFA_set_transition(problem1_d, 1, '0', 3);
	DFA_set_transition(problem1_d, 2, '0', 0);
	DFA_set_transition(problem1_d, 2, '1', 3);
	DFA_set_transition(problem1_d, 3, '0', 1);
	DFA_set_transition(problem1_d, 3, '1', 2);
	DFA_set_accepting(problem1_d, 0, TRUE);
    DFA_print(problem1_d);

	printf("\n Problem 1 (e) \n");


	printf("\n-----------------------------PROBLEM 2----------------------------- \n");

	printf("Problem 2 (a) \n");
	NFA *problem2_a = NFA_new(4);
    NFA_add_transition(problem2_a, 0,'m',1);
    NFA_add_transition(problem2_a, 1,'a',2);
    NFA_add_transition(problem2_a, 2,'n',3);
    NFA_add_transition_all(problem2_a, 0,0);
    NFA_set_accepting(problem2_a, 3, TRUE);


    printf("Problem 2 (b) \n");

    NFA *problem2_b = NFA_new(20);
    NFA_add_transition_all(problem2_b, 0, 0);

    NFA_add_transition(problem2_b, 0, 'a', 1);
    NFA_add_transition_all(problem2_b, 1, 1);
    NFA_add_transition(problem2_b, 1, 'a', 2);
    NFA_add_transition_all(problem2_b, 2, 2);

    NFA_add_transition(problem2_b, 0, 'g', 3);
    NFA_add_transition_all(problem2_b, 3, 3);
    NFA_add_transition(problem2_b, 3, 'g', 4);
    NFA_add_transition_all(problem2_b, 4, 4);

    NFA_add_transition(problem2_b, 0, 'h', 5);
    NFA_add_transition_all(problem2_b, 5, 5);
    NFA_add_transition(problem2_b, 5, 'h', 6);
    NFA_add_transition_all(problem2_b, 6, 6);

    NFA_add_transition(problem2_b, 0, 'i', 7);
    NFA_add_transition_all(problem2_b, 7, 7);
    NFA_add_transition(problem2_b, 7, 'i', 8);
    NFA_add_transition_all(problem2_b, 8, 8);

    NFA_add_transition(problem2_b, 0, 'n', 9);
    NFA_add_transition_all(problem2_b, 9, 9);
    NFA_add_transition(problem2_b, 9, 'n', 10);
    NFA_add_transition_all(problem2_b, 10, 10);
    NFA_add_transition(problem2_b, 10, 'n', 11);
    NFA_add_transition_all(problem2_b, 11, 11);

    NFA_add_transition(problem2_b, 0, 'o', 12);
    NFA_add_transition_all(problem2_b, 12, 12);
    NFA_add_transition(problem2_b, 12, 'o', 13);
    NFA_add_transition_all(problem2_b, 13, 13);

    NFA_add_transition(problem2_b, 0, 's', 14);
    NFA_add_transition_all(problem2_b, 14, 14);
    NFA_add_transition(problem2_b, 14, 's', 15);
    NFA_add_transition_all(problem2_b, 15, 15);

    NFA_add_transition(problem2_b, 0, 't', 16);
    NFA_add_transition_all(problem2_b, 16, 16);
    NFA_add_transition(problem2_b, 16, 't', 17);
    NFA_add_transition_all(problem2_b, 17, 17);

    NFA_add_transition(problem2_b, 0, 'w', 18);
    NFA_add_transition_all(problem2_b, 18, 18);
    NFA_add_transition(problem2_b, 18, 'w', 19);
    NFA_add_transition_all(problem2_b, 19, 19);

    NFA_set_accepting(problem2_b, 2, TRUE);
    NFA_set_accepting(problem2_b, 4, TRUE);
    NFA_set_accepting(problem2_b, 6, TRUE);
    NFA_set_accepting(problem2_b, 8, TRUE);
    NFA_set_accepting(problem2_b, 11, TRUE);
    NFA_set_accepting(problem2_b, 13, TRUE);
    NFA_set_accepting(problem2_b, 15, TRUE);
    NFA_set_accepting(problem2_b, 17, TRUE);
    NFA_set_accepting(problem2_b, 19, TRUE);

    printf("Problem 2 (c) \n");

    NFA *problem2_c = NFA_new(9);
    NFA_add_transition_str(problem2_c, 0, "abc", 0);
    NFA_add_transition(problem2_c, 0, 'a', 1);
    NFA_add_transition(problem2_c, 1, 'b', 2);
    NFA_add_transition(problem2_c, 2, 'c', 3);
    NFA_add_transition_str(problem2_c, 3, "abc", 3);
    NFA_add_transition(problem2_c, 0, 'b', 4);
    NFA_add_transition(problem2_c, 4, 'a', 5);
    NFA_add_transition_str(problem2_c, 5, "abc", 5);
    NFA_add_transition(problem2_c, 0, 'b', 6);
    NFA_add_transition(problem2_c, 6, 'b', 7);
    NFA_add_transition(problem2_c, 7, 'a', 8);
    NFA_add_transition_str(problem2_c, 8, "abc", 8);
    NFA_set_accepting(problem2_c, 3, TRUE);
    NFA_set_accepting(problem2_c, 5, TRUE);
    NFA_set_accepting(problem2_c, 8, TRUE);


	printf("\n-----------------------------PROBLEM 3-----------------------------");


















	//DFA *trial  = DFA_new(3);
    //printf("trial");
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

    printf("NFA p1 \n");
    NFA *p1 = NFA_new(2);
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

    printf("DFA p1 \n");

    DFA *dfa_p1 = NFA_to_DFA(p1);
    //DFA_print(dfa_p1);
    printf("%d \n", DFA_execute(dfa_p1, ""));
    printf("%d \n", DFA_execute(dfa_p1, "a"));
    printf("%d \n", DFA_execute(dfa_p1, "ab"));
    printf("%d \n", DFA_execute(dfa_p1, "abc"));
    printf("%d \n", DFA_execute(dfa_p1, "def"));
    printf("%d \n", DFA_execute(dfa_p1, "abbbaabababababa"));

    printf("NFA p2 \n");

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

    DFA *p2_dfa = NFA_to_DFA(p2);
    printf("dfa p2 \n");
    printf("%d \n", DFA_execute(p2_dfa, ""));
    printf("%d \n", DFA_execute(p2_dfa, "abbbb"));
    printf("%d \n", DFA_execute(p2_dfa, "01abc01"));
    printf("%d \n", DFA_execute(p2_dfa, "cccabcaaa"));
    printf("%d \n", DFA_execute(p2_dfa, "abcabcabcabcabc"));

    NFA_free(p2);

    /*NFA *p3 = NFA_new(9);
    NFA_add_transition_str(p3, 0, "abc", 0);
    NFA_add_transition(p3, 0, 'a', 1);
    NFA_add_transition(p3, 1, 'b', 2);
    NFA_add_transition(p3, 2, 'c', 3);
    NFA_add_transition_str(p3, 3, "abc", 3);
    NFA_add_transition(p3, 0, 'b', 4);
    NFA_add_transition(p3, 4, 'a', 5);
    NFA_add_transition_str(p3, 5, "abc", 5);
    NFA_add_transition(p3, 0, 'b', 6);
    NFA_add_transition(p3, 6, 'b', 7);
    NFA_add_transition(p3, 7, 'a', 8);
    NFA_add_transition_str(p3, 8, "abc", 8);
    NFA_set_accepting(p3, 3, TRUE);
    NFA_set_accepting(p3, 5, TRUE);
    NFA_set_accepting(p3, 8, TRUE);

    DFA *p3_dfa = NFA_to_DFA(p3);
    printf("nfa p3 \n");
    printf("%d \n", NFA_execute(p3, ""));
    printf("%d \n", NFA_execute(p3, "abbbb"));
    printf("%d \n", NFA_execute(p3, "01abc01"));
    printf("%d \n", NFA_execute(p3, "cccabcaaa"));
    printf("%d \n", NFA_execute(p3, "abcabcabcabcabc"));
	printf("%d \n", NFA_execute(p3, "ccccbbaccc"));


    printf("dfa p3 \n");
    printf("%d \n", DFA_execute(p3_dfa, ""));
    printf("%d \n", DFA_execute(p3_dfa, "abbbb"));
    printf("%d \n", DFA_execute(p3_dfa, "01abc01"));
    printf("%d \n", DFA_execute(p3_dfa, "cccabcaaa"));
    printf("%d \n", DFA_execute(p3_dfa, "abcabcabcabcabc"));
    printf("%d \n", DFA_execute(p3_dfa, "ccccbbaccc"));*/


    /*NFA *problem2_b = NFA_new(20);
    
    printf("problem2_b \n");
    NFA_add_transition_all(problem2_b, 0, 0);

    NFA_add_transition(problem2_b, 0, 'a', 1);
    NFA_add_transition_all(problem2_b, 1, 1);
    NFA_add_transition(problem2_b, 1, 'a', 2);
    NFA_add_transition_all(problem2_b, 2, 2);

    NFA_add_transition(problem2_b, 0, 'g', 3);
    NFA_add_transition_all(problem2_b, 3, 3);
    NFA_add_transition(problem2_b, 3, 'g', 4);
    NFA_add_transition_all(problem2_b, 4, 4);

    NFA_add_transition(problem2_b, 0, 'h', 5);
    NFA_add_transition_all(problem2_b, 5, 5);
    NFA_add_transition(problem2_b, 5, 'h', 6);
    NFA_add_transition_all(problem2_b, 6, 6);

    NFA_add_transition(problem2_b, 0, 'i', 7);
    NFA_add_transition_all(problem2_b, 7, 7);
    NFA_add_transition(problem2_b, 7, 'i', 8);
    NFA_add_transition_all(problem2_b, 8, 8);

    NFA_add_transition(problem2_b, 0, 'n', 9);
    NFA_add_transition_all(problem2_b, 9, 9);
    NFA_add_transition(problem2_b, 9, 'n', 10);
    NFA_add_transition_all(problem2_b, 10, 10);
    NFA_add_transition(problem2_b, 10, 'n', 11);
    NFA_add_transition_all(problem2_b, 11, 11);

    NFA_add_transition(problem2_b, 0, 'o', 12);
    NFA_add_transition_all(problem2_b, 12, 12);
    NFA_add_transition(problem2_b, 12, 'o', 13);
    NFA_add_transition_all(problem2_b, 13, 13);

    NFA_add_transition(problem2_b, 0, 's', 14);
    NFA_add_transition_all(problem2_b, 14, 14);
    NFA_add_transition(problem2_b, 14, 's', 15);
    NFA_add_transition_all(problem2_b, 15, 15);

    NFA_add_transition(problem2_b, 0, 't', 16);
    NFA_add_transition_all(problem2_b, 16, 16);
    NFA_add_transition(problem2_b, 16, 't', 17);
    NFA_add_transition_all(problem2_b, 17, 17);

    NFA_add_transition(problem2_b, 0, 'w', 18);
    NFA_add_transition_all(problem2_b, 18, 18);
    NFA_add_transition(problem2_b, 18, 'w', 19);
    NFA_add_transition_all(problem2_b, 19, 19);

    NFA_set_accepting(problem2_b, 2, TRUE);
    NFA_set_accepting(problem2_b, 4, TRUE);
    NFA_set_accepting(problem2_b, 6, TRUE);
    NFA_set_accepting(problem2_b, 8, TRUE);
    NFA_set_accepting(problem2_b, 11, TRUE);
    NFA_set_accepting(problem2_b, 13, TRUE);
    NFA_set_accepting(problem2_b, 15, TRUE);
    NFA_set_accepting(problem2_b, 17, TRUE);
    NFA_set_accepting(problem2_b, 19, TRUE);

    printf("%d \n", NFA_execute(problem2_b, "washington"));

    DFA *problem2_b1 = NFA_to_DFA(problem2_b);*/


    //printf(" DFA NFA TEST %d \n", DFA_execute(dfa_problem2_b, "washington"));*/


    /*NFA *problem1 = NFA_new(4);
    printf("problem1 \n");
    NFA_add_transition(problem1, 0,'m',1);
    NFA_add_transition(problem1, 1,'a',2);
    NFA_add_transition(problem1, 2,'n',3);
    NFA_add_transition_all(problem1, 0,0);
    NFA_set_accepting(problem1, 3, TRUE);
    //printf("%d \n", NFA_execute(problem1, "man"));
    //printf("%d \n", NFA_execute(problem1, "aewifasdciuandvx"));
    //printf("%d \n", NFA_execute(problem1, "amanb"));
    //printf("%d \n", NFA_execute(problem1, "manabc"));
    //printf("%d \n", NFA_execute(problem1, "defman"));*/
  

    /*DFA *dfa_test = NFA_to_DFA(problem1);
    printf("dfa_test \n");
    //DFA_print(dfa_test);
    printf("DFA STUFF \n%d \n", DFA_execute(dfa_test, "man"));
    printf("%d \n", DFA_execute(dfa_test, "aewifasdciuandvx"));
    printf("%d \n", DFA_execute(dfa_test, "amanb"));
    printf("%d \n", DFA_execute(dfa_test, "manabc"));
    printf("%d \n", DFA_execute(dfa_test, "defman"));
    DFA_free(dfa_test);
    NFA_free(problem1);*/


    //printf("%d \n", DFA_execute(dfa_test, "manmanman"));
    //printf("%d \n", DFA_execute(dfa_test, "manmanman1"));


    //DFA_free(dfa_test);*/

	return 0;
}