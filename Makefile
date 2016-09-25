all: test
	
test: IntSet.c nfa.c dfa.c main_file.c LinkedList.c
	gcc IntSet.c nfa.c dfa.c main_file.c LinkedList.c -o test

clean: 
	rm *o test