#!/bin/bash
gcc -c pig.c -o pig.o
gcc -c test_pig.c -o test_pig.o
gcc -c piglatin.c -o piglatin.o
gcc pig.o test_pig.o -o test_pig
gcc pig.o piglatin.o -o piglatin
