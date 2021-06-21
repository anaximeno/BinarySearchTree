#!/bin/bash

echo Compiling...

gcc -Wall -O2 -Iinclude -c ./main.c -o obj/Release/main.o
gcc  -o binarysearchtree obj/Release/main.o obj/Release/src/common.o obj/Release/src/forest.o obj/Release/src/linkedlist.o obj/Release/src/treeprinter.o  -s

echo finished.
