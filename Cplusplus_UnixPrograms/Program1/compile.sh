#!/bin/bash
#Ryan Hosford
#rph160030@utdallas.edu
#CS3377

# Compiles the files and output the steps

g++ -c main.cpp
echo "Compiled main.cpp"
g++ -c otherClass.cpp
echo "Compiled otherClass.cpp"
g++ -o project1 main.o otherClass.o
echo "Linked main.o and otherClass.o"
echo "Output file is project1"
