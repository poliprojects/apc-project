#!/bin/bash

# Run this script while in time folder!

# Remove files, if any, of a previous run of this script (the ones not starting
# with "time" will not be deleted)
rm -rf time*.txt

# Set number of iterations
n=100

# Execute all programs and write execution times into the corresponding files:
# * grep 'μ' extracts from the output the line with the duration time
# * grep -oP "\d{4,}" further extracts a sequence of 4 or more digits
# * >> <file>.txt appends the found number to the corresponding file
for (( i=1; i<=$n; i++ )); do
    # Test number 4, parallel
    mpiexec -np 2 ../main 4 IserNor | grep 'μ' | grep -oP "\d{4,}" >> \
        timepar4.txt
    # Test number 4, sequential
    ../main 4 IserNor | grep 'μ' | grep -oP "\d{4,}" >> timeseq4.txt

    # Test number 5, parallel
    mpiexec -np 2 ../main 5 IserNor | grep 'μ' | grep -oP "\d{4,}" >> \
        timepar5.txt
    # Test number 5, sequential
    ../main 5 IserNor | grep 'μ' | grep -oP "\d{4,}" >> timeseq5.txt

    # Test number 6, parallel
    mpiexec -np 2 ../main 6 IserNor | grep 'μ' | grep -oP "\d{4,}" >> \
        timepar6.txt
    # Test number 6, sequential
    ../main 6 IserNor | grep 'μ' | grep -oP "\d{4,}" >> timeseq6.txt

    echo "Round $i of $n"
done

# Remove produced solution files
rm sol*.txt


# Compute sum of times for each file and write output into timeres.txt
echo "Parallel 4:" >> timeres.txt
awk '{ sum += $1 } END { print sum }' timepar4.txt >> timeres.txt
echo >> timeres.txt

echo "Sequent. 4:" >> timeres.txt
awk '{ sum += $1 } END { print sum }' timeseq4.txt >> timeres.txt
echo >> timeres.txt

echo "Parallel 5:" >> timeres.txt
awk '{ sum += $1 } END { print sum }' timepar5.txt >> timeres.txt
echo >> timeres.txt

echo "Sequent. 5:" >> timeres.txt
awk '{ sum += $1 } END { print sum }' timeseq5.txt >> timeres.txt
echo >> timeres.txt

echo >> timeres.txt

echo "Parallel 6:" >> timeres.txt
awk '{ sum += $1 } END { print sum }' timepar6.txt >> timeres.txt
echo >> timeres.txt

echo "Sequent. 6:" >> timeres.txt
awk '{ sum += $1 } END { print sum }' timeseq6.txt >> timeres.txt

echo "Sums were saved into the timeres.txt file"
