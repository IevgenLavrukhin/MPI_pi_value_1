
all: compile 

compile: 
	mpicc -std=c99 -lm pi_MPI.c -o run


