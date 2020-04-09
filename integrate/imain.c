#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include "integrate.h"

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    double begin = argc > 1 ? atof(argv[1]) : 0;
    double end = argc > 2 ? atof(argv[2]) : 2;
    int num_points = argc > 3 ? atoi(argv[3]) : 10000;

    double results[world_size-1];
    int modulo = num_points % world_size;
    int equal_share = (num_points - modulo) / world_size;
    int n = equal_share + (world_rank < modulo ? 1 : 0);
    double x = (end-begin) / num_points;
    double b = (world_rank < modulo ? equal_share*world_rank : (equal_share+1)*modulo + (world_rank-modulo)*equal_share) * x;
    double e = b + x*n;
    
    MPI_Request request;
    MPI_Status status;

    if (world_rank == 0) {
        double result = integrate(fun, b, e, n);

        for (int i=1; i<world_size; i++) {
            MPI_Irecv(&results[i-1], 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);
        }    

        for (int i=0; i<world_size-1; i++) result += results[i];
        printf("Result is: %f\n", result);
    } else {
        results[world_rank-1] = integrate(fun, b, e, n);
        MPI_Isend(&results[world_rank-1], 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
    }

    MPI_Finalize();
}