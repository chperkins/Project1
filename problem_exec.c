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

NFA *washington () {
	printf(" \n Problem 2 (b) \n");
    printf("Strings that contain more than one each of the letters in \"washington\" other than n, or more than two n\'s \n");

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

    printf("Test for \"washingtonw\": %d \n", NFA_execute(problem2_b, "washingtonw"));
    printf("Test for \"axyzuioa\": %d \n", NFA_execute(problem2_b, "axyzuioa"));
    printf("Test for \"nann\": %d \n", NFA_execute(problem2_b, "nann"));
    printf("Test for \"washington\": %d \n", NFA_execute(problem2_b, "washington"));
    printf("Test for \"\": %d \n", NFA_execute(problem2_b, ""));

    printf("Problem 2 (c) \n");

    return problem2_b;
}

DFA *ab () {
printf("-----------------------------PROBLEM 1----------------------------- \n"); 

	printf("Problem 1 (a) \n");
    printf("Exactly the string \"ab\" \n");
	DFA *problem1_a = DFA_new(3);
	DFA_set_transition(problem1_a, 0, 'a', 1);
	DFA_set_transition(problem1_a, 1, 'b', 2);
	DFA_set_accepting(problem1_a, 2, TRUE);
    DFA_print(problem1_a);
    printf("Test for \"ab\": %d \n", DFA_execute(problem1_a, "ab"));
    printf("Test for \"cde\": %d \n", DFA_execute(problem1_a, "cde"));
    printf("Test for \"\": %d \n", DFA_execute(problem1_a, ""));

    return problem1_a;
}

DFA *start_ab () {
printf("\n Problem 1 (b) \n");
    printf("Any string that starts with the characters \"ab\" \n");
	DFA *problem1_b = DFA_new(3);
	DFA_set_transition(problem1_b, 0, 'a', 1);
	DFA_set_transition(problem1_b, 1, 'b', 2);
	DFA_set_transition_all(problem1_b, 2, 2);
	DFA_set_accepting(problem1_b, 2, TRUE);
    DFA_print(problem1_b);
    printf("Test for \"ab\": %d \n", DFA_execute(problem1_b, "ab"));
    printf("Test for \"abcd\": %d \n", DFA_execute(problem1_b, "abcd"));
    printf("Test for \"cde\": %d \n", DFA_execute(problem1_b, "cde"));
    printf("Test for \"\": %d \n", DFA_execute(problem1_b, ""));
    return problem1_b;
}

DFA *even_num_1 () {
printf("\n Problem 1 (c) \n");
    printf("Binary input with an even number of 1\'s \n");
	DFA *problem1_c = DFA_new(2);
	DFA_set_transition(problem1_c, 0, '1', 1);
	DFA_set_transition(problem1_c, 1, '1', 0);
	DFA_set_transition(problem1_c, 0, '0', 0);
	DFA_set_transition(problem1_c, 1, '0', 1);
	DFA_set_accepting(problem1_c, 0, TRUE);
    DFA_print(problem1_c);
    printf("Test for \"11\": %d \n", DFA_execute(problem1_c, "11"));
    printf("Test for \"1010101011\": %d \n", DFA_execute(problem1_c, "1010101011"));
    printf("Test for \"\": %d \n", DFA_execute(problem1_c, ""));
    printf("Test for \"1\": %d \n", DFA_execute(problem1_c, "1"));
    printf("Test for \"0001011\": %d \n", DFA_execute(problem1_c, "0001011"));
    return problem1_c;
}


DFA *even_num_01 () {
    printf("\n Problem 1 (d) \n");
    printf("Binary input with an even number of both 0\'s and 1\'s \n");
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
    printf("Test for \"11\": %d \n", DFA_execute(problem1_d, "11"));
    printf("Test for \"00\": %d \n", DFA_execute(problem1_d, "00"));
    printf("Test for \"1010101011\": %d \n", DFA_execute(problem1_d, "1010101011"));
    printf("Test for \"\": %d \n", DFA_execute(problem1_d, ""));
    printf("Test for \"1\": %d \n", DFA_execute(problem1_d, "1"));
    printf("Test for \"100\": %d \n", DFA_execute(problem1_d, "100"));
    printf("Test for \"101\": %d \n", DFA_execute(problem1_d, "101"));
    printf("Test for \"0001011\": %d \n", DFA_execute(problem1_d, "0001011"));
    return problem1_d;
}


NFA *end_in_man() {
printf("\n-----------------------------PROBLEM 2----------------------------- \n");

	printf("Problem 2 (a) \n");
    printf("Strings ending in \"man\" \n");
	NFA *problem2_a = NFA_new(4);
    NFA_add_transition(problem2_a, 0,'m',1);
    NFA_add_transition(problem2_a, 1,'a',2);
    NFA_add_transition(problem2_a, 2,'n',3);
    NFA_add_transition_all(problem2_a, 0,0);
    NFA_set_accepting(problem2_a, 3, TRUE);
    printf("Test for \"man\": %d \n", NFA_execute(problem2_a, "man"));
    printf("Test for \"dczeman\": %d \n", NFA_execute(problem2_a, "dczeman"));
    printf("Test for \"manmann\": %d \n", NFA_execute(problem2_a, "manmann"));
    printf("Test for \"jwiefo\": %d \n", NFA_execute(problem2_a, "jwiefo"));
    printf("Test for \"\": %d \n", NFA_execute(problem2_a, ""));
    return problem2_a;
}
