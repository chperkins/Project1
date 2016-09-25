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

    DFA *problem1_e = contain_moo();

	NFA *problem2_a = end_in_man();

    NFA *problem2_b = washington();

    NFA *problem2_c = contain_abc_ba_bba ();

    DFA *problem3_a = end_in_man_dfa(problem2_a);

    //DFA *problem3_b = washington_dfa(problem2_b);
    
    DFA *problem3_c = contain_abc_ba_bba_dfa (problem2_c);
    



	return 0;
}