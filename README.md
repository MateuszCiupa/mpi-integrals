# mpi-integrals
Parallel numerical integration with Message Passing Interface

## Getting started

Build executables by using `integrate/makefile`.
```
make clean [main|group|imain]
mpirun -n 4 ./integrate 0 2 10000
```

Run with default values (begin=0, end=2, points=10000, proc=4)


```
make clean [main|group|imain] run 
```

Or set them yourself

```
make clean [main|group|imain] run begin=100 end=1000 points=1000000 proc=4
```

## Source

- MPI_Send *&* MPI_Recv as `integrate/main.c`
- MPI_Scatter *&* MPI_Gather as `integrate/group.c`
- MPI_Isend *&* MPI_Irecv as `integrate/imain.c`
