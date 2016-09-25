CC=gcc

all: test
	
test: main_file.o nfa.o dfa.o LinkedList.o IntSet.o 
	$(CC) main_file.o nfa.o dfa.o LinkedList.o IntSet.o -o test

main_file.o: main_file.c
	$(CC) -c main_file.c

nfa.o: nfa.c
	$(CC) -c nfa.c

dfa.o: dfa.c
	$(CC) -c dfa.c

LinkedList.o: LinkedList.c
	$(CC) -c LinkedList.c

IntSet.o: IntSet.c
	$(CC) -c IntSet.c

clean: 
	rm *o test