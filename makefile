# Makefile

# Compile the program
prog: fibon.o 
	gcc -Wall -ansi -pedantic fibon.o -o prog

# Compile fibon.c
fibon.o: fibon.c types.h fibon.h files.h
	gcc -Wall -ansi -pedantic -c fibon.c

