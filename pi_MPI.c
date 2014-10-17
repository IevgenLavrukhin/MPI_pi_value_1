#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define PI 3.141592653589793

int main(int argc, char **argv) {

	int rank, size;
	
	int N_points = atoi (argv [1]);	
	int counter = 0;

	MPI_Init (&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	MPI_Comm_size (MPI_COMM_WORLD, &size);

        //printf("I am rank = %d of %d \n", rank, size); 
	
	srand(size*size+size*size*rank -size); //to generate different numbers for different processors
	
	for (int i=0; i<N_points; i++) { 
	      double x =1.0*rank/size + 1.0/size * rand()/(double) RAND_MAX;
              double y = rand()/(double) RAND_MAX ;
	      if (x*x + y*y <= 1) counter ++;
        } 
       
	double area = 1.0*counter/N_points;
	double total_area;
	
	MPI_Reduce(&area, &total_area, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	double my_pi = 4*total_area/size;
        if (0 == rank) printf("Obtaine Pi value: %lf \n Error, %: %lf \n ", my_pi, 100*sqrt((PI-my_pi)*(PI-my_pi))/PI);

        MPI_Finalize();

return 0;
}



