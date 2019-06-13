# Instructions
You will need a terminal to run the following commands.

## Downloading from GitHub
Run ```git clone https://github.com/poliprojects/apc-project.git```

## Installing
Compile running ```make```

## Usage
* Run ```main``` or ```./main```, providing the following parameters:
	* test number [ 1, 2, 3, 4 ]
	* solver identification code [ FE, adapFE, RK, adapRK, RK4, IserNor ]
* Optional parameters:
	* initial step [ any double, default set to 0.1 ]
	* tolerance [ any double, default set to 0.01 ]
* Example: ```./main 3 RK 0.2 1e-3```
* Example: ```./main 2 adapFE```
* To execute the IserNor method in parallel, include ```mpiexec -np 2``` when
    calling main
* Example: ```mpiexec -np 2 ./main 4 IserNor```
* After running, information about the equation solved will appear on screen
* The solution and time instants will be saved in solution_<#test>\_<method>.txt
* Run the ```check_solutions.m``` file with Matlab selecting the number of the
test to see a plot of exact vs computed solution

## Adding new test functions
1) Add a new EquationFunction in the ```equations.cpp``` and
```equations.hpp``` files
2) In main.cpp ... (TODO)
