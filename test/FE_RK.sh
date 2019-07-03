#!/bin/bash

# Run this script while in test folder!

# Remove files, if any, of a previous run of this script
rm -rf FE.txt
rm -rf RK.txt

# Set number of iterations
n=200

# Execute all programs and write execution times into the corresponding files:
# * grep 'μ' extracts from the output the line with the duration time
# * grep -oP "\d{4,}" further extracts a sequence of 4 or more digits
# * >> <file>.txt appends the found number to the corresponding file

# Test number chosen to compare efficiency of FE class
Test=6

for (( i=1; i<=$n; i++ )); do

    ../main $Test FE | grep 'μ' | grep -oP "\d{4,}" >> FE.txt

    ../main $Test RK | grep 'μ' | grep -oP "\d{4,}" >> RK.txt

    echo "Round $i of $n"
done

# Remove produced solution files
rm sol*.txt
