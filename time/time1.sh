#!/bin/bash

rm -rf time*.txt
rm -rf timeres.txt

for i in {1..100}; do
	mpiexec -np 2 ./main 5 IserNor | grep 'μ' | tee -a timepar5.txt
	./main 5 IserNor | grep 'μ' | tee -a timeseq5.txt

	mpiexec -np 2 ./main 6 IserNor | grep 'μ' | tee -a timepar6.txt
	./main 6 IserNor | grep 'μ' | tee -a timeseq6.txt
done
