
#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "nfa.h"
#include "IntSet.h"

extern NFA *washington ();
extern DFA *ab();
extern DFA *start_ab();
extern DFA *even_num_1();
extern DFA *even_num_01 ();
extern NFA *end_in_man();
extern NFA *contain_abc_ba_bba ();
extern DFA *end_in_man_dfa (NFA *problem2_a);
extern DFA *washington_dfa(NFA *problem2_b);
extern DFA *contain_abc_ba_bba_dfa (NFA *problem2_c);

extern DFA *contain_moo();
extern NFA *contain_loo_NFA();
