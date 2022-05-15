#!/bin/bash
gcc -c -Wall -fPIC -D_GNU_SOURCE add.c
gcc add.o -shared -o lib_arytmdyn.so
gcc -c main.c -o main.o
gcc main.o -L. -l_arytmdyn -o main.out