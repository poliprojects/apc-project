#!/bin/bash

rm -rf timeres.txt

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
