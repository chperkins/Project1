# 
# File: Makefile
# Makefile compiles and runs project
# For different compilier change var CC
# To change name of executable change var EXECUTABLE
#
# Made following tutorial from http://mrbook.org/blog/tutorials/make/
#

CC=gcc
CFLAGS=
SOURCES=main_file.c nfa.c dfa.c LinkedList.c IntSet.c problem_exec.c nfa_dfa.c
OBJECTS=$(SOURCES: .c=.o)
EXECUTABLE=test

all: $(EXECUTABLE)
	#./$(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

main_file.o: main_file.c
	$(CC) $(CFLAGS) main_file.c

nfa.o: nfa.c
	$(CC) $(CFLAGS) nfa.c

dfa.o: dfa.c
	$(CC) $(CFLAGS) dfa.c

LinkedList.o: LinkedList.c
	$(CC) $(CFLAGS) LinkedList.c

IntSet.o: IntSet.c
	$(CC) $(CFLAGS) IntSet.c

problem_exec.o: problem_exec.c
	$(CC) $(CFLAGS) problem_exec.c

nfa_dfa.o: nfa_dfa.c
	$(CC) $(CFLAGS) nfa_dfa.c

clean: 
	rm *o $(EXECUTABLE)