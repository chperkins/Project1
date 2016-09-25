/*
* Contributors: Maria Weber, Charlie Perkins, Luba Le Xuan
* Professor: George Ferguson
*
*/
#ifndef _dfa_h
#define _dfa_h

#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "dfa.h"

/*create new DFA*/
DFA *DFA_new(int n) {
    DFA *dfa = (DFA*)malloc(sizeof(DFA)); /*frees space for the dfa*/
    dfa->nstates = n;  
    dfa->current_state = 0; /*sets starting state to 0*/
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
		dfa->states[src].transitions[i] = dst; /*sets all transitions to destination*/
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

void DFA_free(DFA *dfa){

	/*for(int i=0; i< DFA_get_size(dfa); i++){
		DFA_State *state = &dfa->states[i];
		free(state);
	}*/
	free(dfa->states); /*frees memory allocates for the array of states*/
	free(dfa); /*finally frees the dfa*/
}

void DFA_print(DFA *dfa){
	/* Print the DFA in the format
	 * Node origin_node: |symbol, dest_node|
	 * If there is a transition all, output is |all -excluded_sym, dest_node|
	 */

	/* Iterate through each state in the DFA, checking if it has a transition and to what state.*/
	for(int i=0; i < DFA_get_size(dfa); i++){
		printf("\nStart State %d: ", i);

		/* Create an array to count how many transitions there are from current state to every other state*/
		int trans_all[DFA_get_size(dfa)];
		for(int k=0; k < DFA_get_size(dfa); k++){
			trans_all[k] = 0;//Initialize array
		}

		//For each transition from current state, increment the array at the index of the destination state
		for(int x =32; x < 128; x++){
			int dest = dfa->states[i].transitions[x]; //Get the destination of the transition from current state
			if(dest != -1){
				trans_all[dest] += 1;
			}
		}
		/* Now that we have an array filled with the count of transitions from curr state through possible destinations */
		for(int z =0; z < DFA_get_size(dfa); z++){

			if(trans_all[z] >= 96){ //If there are 96 transitions, it is a transition all
					printf("|all, %d|", z);
			}

			if(trans_all[z] >88 && trans_all[z] <96){//In this case only a few transitions are different from the rest, so we do |all -x -y ...|
				int dest_all = dfa->states[i].transitions[0];
				int diff_dest[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
				int diff_count = 0;

				printf("|all ");

				for(int x=32; x <128; x++){
					int dest = dfa->states[i].transitions[x];
					if(dest != dest_all){
						printf("-\'%c\'", x);
						diff_dest[diff_count] = dest;
						diff_dest[diff_count+1] = x;
						diff_count +=2;
					}
				}
				printf("|\t");

				/*for(int x=0; x<15; x+=2){
					if(diff_dest[x] != -1){
						printf("|%c,%d|", diff_dest[x+1], diff_dest[x]);
					}
				}*/
			}
		}

		
		for (int j = 32; j < DFA_NSYMBOLS; j++){

			int dest = dfa->states[i].transitions[j];

			if(dest != -1 && trans_all[dest] <88){
				printf("|\'%c\',%d|", j, dest);
			}							
		}
	}
		
	printf("\n");
}

int DFA_execute(DFA *dfa, char *input) {
	for(int i=0; input[i] != '\0'; i++) { /*iterates while the input isn't empty*/
		int destination = dfa->states[dfa->current_state].transitions[input[i]]; /*sets teh destination to the transition of input i*/
		DFA_set_current_state(dfa, destination); /*sets current state to the transition*/
		if(dfa->current_state == -1) { /*if no transition, the dfa halts and returns false*/
			return FALSE;
		}
	} /* sets the current state to the transition of the previous state over and over*/
	int final_state = dfa->current_state; /*puts the final state in a temporary*/
	DFA_set_current_state(dfa, 0); /*this allows us to reset the current state to 0*/
	return DFA_get_accepting(dfa, final_state); /*returns accepting value of the final state*/
}


#endif
