#!/bin/bash

gcc -o p MMpthreads.c -lpthread

# Iterate from 1 to 60 threads
for num_threads in {1..20}
do
    # Execute the program with the current thread count
    ./p $num_threads
done
