# Makefile

# Compile the program
prog: fibon.o files.o
	gcc -Wall -ansi -pedantic fibon.o files.o -o prog -lm

# Compile fibon.c
fibon.o: fibon.c types.h fibon.h files.h
	gcc -Wall -ansi -pedantic -c fibon.c

# Compile files.c
files.o: files.c files.h
	gcc -Wall -ansi -pedantic -c files.c 
