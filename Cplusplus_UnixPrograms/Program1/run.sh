#!/bin/bash
#Ryan Hosford
#rph160030@utdallas.edu
#CS3377

#Script that runs program1 a few times with different inputs

echo "Running program with no additional arguments..."
./project1 >> stdout.log 2>> stderr.log 

echo "Running program with 3 additional arguments..."
./project1 Three additional args >> stdout.log 2>> stderr.log

echo "Running program with 5 additional arguments..."
./project1 5 additional arguments 123 321 >> stdout.log 2>> stderr.log

echo "Finished running program."
