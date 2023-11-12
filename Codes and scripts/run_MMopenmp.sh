#!/bin/bash


gcc -o MMopenmp MMopenmp.c -fopenmp


for num_threads in {1..20}
do
    ./MMopenmp $num_threads
done
