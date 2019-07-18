#!/bin/bash

# Total number of test equations
n=7

for (( i=1; i<=$n; i++ )); do

    echo "-------------------------
      Test $i of $n
-------------------------"

    ../main $i FE
    ../main $i RK4 # useless (TODO)
    ../main $i RK4
    ../main $i Heun
    ../main $i RK
    ../main $i IserNor
    # mpiexec -np 2 ../main $i IserNor

    ../main $i adapFE
    ../main $i adapRK4
    ../main $i adapHeun
    ../main $i adapRK
    ../main $i adapIserNor
    # mpiexec -np 2 ../main $i adapIserNor

    mv solution_${i}_FE.txt ../
    mv solution_${i}_RK4.txt ../
    mv solution_${i}_Heun.txt ../
    mv solution_${i}_RK.txt ../
    mv solution_${i}_IserNor.txt ../

    mv solution_${i}_adapFE.txt ../
    mv solution_${i}_adapRK4.txt ../
    mv solution_${i}_adapHeun.txt ../
    mv solution_${i}_adapRK.txt ../
    mv solution_${i}_adapIserNor.txt ../

done
