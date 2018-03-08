all: prog

prog: bst.o linkedListStack.o
	gcc -g -Wall -std=c99 -o prog bst.o linkedListStack.o

bst.o: bst.c bst.h
	gcc -g -Wall -std=c99 -c bst.c

linkedListStack.o: linkedListStack.c linkedListStack.h
	gcc -g -Wall -std=c99 -c linkedListStack.c

clean:	
	rm bst.o
	rm prog
