#!/bin/bash

gcc -c beggar.c -o beggar.o -fsanitize=address
gcc -c queue.c -o queue.o -fsanitize=address
gcc -c util.c -o util.o -fsanitize=address
gcc -c shuffle.c -o shuffle.o -fsanitize=address
gcc -c single.c -o single.o -fsanitize=address
gcc beggar.o queue.o util.o shuffle.o -lgsl -lgslcblas -o beggar -fsanitize=address
gcc single.o queue.o util.o shuffle.o -lgsl -lgslcblas -o single -fsanitize=address
echo "done."
