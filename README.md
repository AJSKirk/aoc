# Advent of Code!

My answers to the Advent of Code annual challenges, in a few different languages. A few notes:

### C

Covers 2020. Some C problems have multiple implementations, following the following schema:

1. `dayNN.c` files just use stdlib C99
2. `dayNN_omp.c` files are built to run using OpenMP for shared memory parallelism. Make sure you have `libomp` on your machine, and make sure you know how to compile them (with GCC this is just `gcc -fopenmp`, MacOS clang requires thre more painful `clang -Xpreprocessor -fopenmp -lomp`
3. `dayNN_mpi.c` files are built to run with MPI message-passing parallelism. These must be compiled with `mpicc` and executed with `mpirun`
