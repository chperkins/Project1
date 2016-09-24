#ifndef _nfa_h_gf
#define _nfa_h_gf

#include <stdbool.h>
#include "IntSet.h"
#include "LinkedList.h"

// Assume input is 7-bit US-ASCII characters
#define NFATODFA_NSYMBOLS 128

#ifndef TRUE
# define TRUE 1
#endif
#ifndef FALSE
# define FALSE 0
#endif

typedef struct  {
   LinkedList *states;

}