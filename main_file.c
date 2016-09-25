#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "nfa.h"
#include "IntSet.h"
#include "dfa.h"
#include <math.h>
#include "LinkedList.h"
#include "nfa_dfa.h"
#include "problem_exec.h"




int main (int argc, char **argv) {

	DFA *problem1_a = ab();

	DFA *problem1_b = start_ab();

	DFA *problem1_c = even_num_1();

	
	DFA *problem1_d = even_num_01 ();

	printf("\n Problem 1 (e) \n");


	NFA *problem2_a = end_in_man();


    NFA *problem2_b = washington();




    /*NFA *problem2_c = NFA_new(9);
    printf("a\'s, b\'s, and c\'s only, contains \"abc\", \"ba\" or \"bba\" anywhere\n");
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

    printf("Test for \"abc\": %d \n", NFA_execute(problem2_c, "abc"));
    printf("Test for \"ba\": %d \n", NFA_execute(problem2_c, "ba"));
    printf("Test for \"bba\": %d \n", NFA_execute(problem2_c, "bba"));
    printf("Test for \"cccabcccc\": %d \n", NFA_execute(problem2_c, "cccabcccc"));

    printf("Test for \"aacc\": %d \n", NFA_execute(problem2_c, "aacc"));
    printf("Test for \"abdddd\": %d \n", NFA_execute(problem2_c, "abdddd"));
    printf("Test for \"\": %d \n", NFA_execute(problem2_c, ""));


	printf("\n-----------------------------PROBLEM 3-----------------------------");

    printf("Conversion of problem 2_a \n");
    DFA *problem2_a_dfa = NFA_to_DFA(problem2_a);
    DFA_print(problem2_a_dfa);
    printf("Test for \"man\": %d \n", DFA_execute(problem2_a_dfa, "man"));
    printf("Test for \"dczeman\": %d \n", DFA_execute(problem2_a_dfa, "dczeman"));
    printf("Test for \"manmann\": %d \n", DFA_execute(problem2_a_dfa, "manmann"));
    printf("Test for \"jwiefo\": %d \n", DFA_execute(problem2_a_dfa, "jwiefo"));
    printf("Test for \"\": %d \n", DFA_execute(problem2_a_dfa, ""));


    /*printf("Conversion of problem 2_b \n");
    DFA *problem2_b_dfa = NFA_to_DFA(problem2_b);
    DFA_print(problem2_b_dfa);
    printf("Test for \"washingtonw\": %d \n", DFA_execute(problem2_b_dfa, "washingtonw"));
    printf("Test for \"axyzuioa\": %d \n", DFA_execute(problem2_b_dfa, "axyzuioa"));
    printf("Test for \"nann\": %d \n", DFA_execute(problem2_b_dfa, "nann"));
    printf("Test for \"washington\": %d \n", DFA_execute(problem2_b_dfa, "washington"));
    printf("Test for \"\": %d \n", DFA_execute(problem2_b_dfa, ""));*/

    /*printf("Conversion of problem 2_c \n");
    DFA *problem2_c_dfa = NFA_to_DFA(problem2_c);
    DFA_print(problem2_c_dfa);
    printf("Test for \"abc\": %d \n", DFA_execute(problem2_c_dfa, "abc"));
    printf("Test for \"ba\": %d \n", DFA_execute(problem2_c_dfa, "ba"));
    printf("Test for \"bba\": %d \n", DFA_execute(problem2_c_dfa, "bba"));
    printf("Test for \"cccabcccc\": %d \n", DFA_execute(problem2_c_dfa, "cccabcccc"));

    printf("Test for \"aacc\": %d \n", DFA_execute(problem2_c_dfa, "aacc"));
    printf("Test for \"abdddd\": %d \n", DFA_execute(problem2_c_dfa, "abdddd"));
    printf("Test for \"\": %d \n", DFA_execute(problem2_c_dfa, ""));*/



	return 0;
}