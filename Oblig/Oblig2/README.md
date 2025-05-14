## How to compile and run MPI program:
mpicc -o para parallel.c -lm
mpirun -np 2 ./para 10 50 50 50 (2 chunks and <num_iters> <kmax> <jmax> <imax>)


## Makefile usage:
### run make which compiles the 2 programs,  used gpt to help me create makefile
make

### run serial:
./serial 10 50 50 50

### run parallel (must have an MPI environment):
mpirun -np 2 ./parallel 10 50 50 50
