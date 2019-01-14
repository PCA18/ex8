//build and run:
//mpicc -Wall -O3 latency.c -o lat.exe && mpirun -np 4 ./lat.exe 1000000

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "utils.h"
//#include <pthread.h>
#include <mpi.h>

 int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

	// Print off a hello world message
	printf("Processor %s, rank %d out of %d processors\n", processor_name, world_rank, world_size-1);
    
	for (int i = 1; i < pow(2,18) + 1; i *=2){
	int msg[i];	
	//int rec_msg[i];
	int rec_msg0[i];
	time_t now;
	time_t not_now;
	time_t cycles;
	rdtsc(now);	
	if (world_rank == 1) {
		MPI_Send(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		//MPI_Recv(&rec_msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	} else if (world_rank == 0) {
		//MPI_Send(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&rec_msg0, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	rdtsc(not_now);
	cycles =+ not_now - now;
	printf("sizeof msg = %ld\n" , sizeof(msg));
	printf("The time is: %.2lf ns\n", cycles/2.5); // cycles/2.5 = ns wegen 2.5 GHz 
	
}
    // Finalize the MPI environment.
    MPI_Finalize();
}
