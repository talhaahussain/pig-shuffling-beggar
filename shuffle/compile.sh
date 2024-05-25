#!/bin/bash
gcc -c util.c -o util.o
gcc -c riffle.c -o riffle.o
gcc -c demo_shuffle.c -o demo_shuffle.o
gcc -c quality.c -o quality.o
gcc util.o riffle.o demo_shuffle.o -o demo_shuffle
gcc util.o riffle.o quality.o -o quality
