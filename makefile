# Makefile

# Compile the program
prog: fibon.c types.h fibon.h
	gcc -Wall -ansi -pedantic fibon.c -o prog

