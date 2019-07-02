#!/bin/bash

# Total number of test equations
n=2

for (( i=1; i<=$n; i++ )); do

    echo "-------------------------
      Test $i of $n
-------------------------"

    ./main $i FE
    ./main $i RK4 # useless (TODO)
    ./main $i RK4
    ./main $i Heun
    ./main $i RK
    ./main $i IserNor
    # mpiexec -np 2 ./main $i IserNor

    ./main $i adapFE
    ./main $i adapRK4
    ./main $i adapHeun
    ./main $i adapRK
    ./main $i adapIserNor
    # mpiexec -np 2 ./main $i adapIserNor

done
