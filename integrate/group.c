#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <stddef.h>
#include "integrate.h"

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    share_t *shares;
    share_t received;

    // MPI STRUCTURE BEGIN
    const int nitems = 3;
    int blocklengths[3] = { 1, 1, 1 };
    MPI_Datatype types[3] = { MPI_DOUBLE, MPI_DOUBLE, MPI_INT };
    MPI_Datatype mpi_share_type;
    MPI_Aint offsets[3];

    offsets[0] = offsetof(share_t, b);
    offsets[1] = offsetof(share_t, e);
    offsets[2] = offsetof(share_t, n);

    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_share_type);
    MPI_Type_commit(&mpi_share_type);
    // MPI STRUCTURE END

    if (world_rank == 0) {
        shares = malloc(sizeof(share_t) * world_size);
        double begin = argc > 1 ? atof(argv[1]) : 0;
        double end = argc > 2 ? atof(argv[2]) : 2;
        int num_points = argc > 3 ? atoi(argv[3]) : 10000;
        split_shares(shares, world_size, begin, end, num_points);
    }

    MPI_Scatter(shares, 1, mpi_share_type, &received, 1, mpi_share_type, 0, MPI_COMM_WORLD);

    double result = integrate(fun, received.b, received.e, received.n);
    double *results = world_rank == 0 ? malloc(sizeof(double)*world_size) : NULL;

    MPI_Gather(&result, 1, MPI_DOUBLE, results, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        double final = 0;
        for (int i=0; i<world_size; i++)
            final += results[i];
        printf("Result is: %f\n", final);
        free(results);
        free(shares);
    }

    MPI_Finalize();
}