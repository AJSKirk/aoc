# Advent of Code!

My answers to the Advent of Code annual challenges, in a few different languages. 

I like teaching people how to code better, and I like learning how to code better! Don't hesitate to reach out if you haave questions about what I've done, or if you have comments on how I could do it better.

A few notes:

### C
Covers 2020. Some C problems have multiple implementations, following the following schema. Makefiles aren't included as they're all straightforward one-file scripts, I might change this if I need to link multiple files together on larger problems:

1. `dayNN.c` files just use stdlib C99
2. `dayNN_omp.c` files are built to run using OpenMP for shared memory parallelism. Make sure you have `libomp` on your machine, and make sure you know how to compile them (with GCC this is just `gcc -fopenmp`, if you're living that LLVM life clang can require you to explicitly pass the preprocessor instructuons with `clang -Xpreprocessor -fopenmp -lomp`
3. `dayNN_mpi.c` files are built to run with MPI message-passing parallelism. These must be compiled with `mpicc` and executed with `mpirun`

All C files are intended to be run on STDIN, this could be from an input redirect (`dayNN < inputs/dayNN.txt`) or piped from an AoC command line tool (I use [Blitzen](https://github.com/kunalb/blitzen) by [kunalb](https://github.com/kunalb/)). Both approaches work fine on the parallelised code as well.

### Fortran
Fortran solutions are written to be shiny modern 2008/2018 Coarray Fortran, though many will compile as far back as Fortran 90. I use the GCC Fortran compiler, so should be easy enough to compile.

### Python
Some of these are silly solutions for fun. All python solutions take the name of an `input` file as their only argument. Files are used instead of STDIN to align with a work competition I was organising for Python users.

All standard library Python, except for one or two that make use of NumPy
