# Adaptive Numerical Solvers for Ordinary Differential Equations
## Instructions
You will need a terminal to run the following commands.

### Downloading from GitHub
Run ```git clone https://github.com/poliprojects/apc-project.git```

### Installing
Compile running ```make```

### Usage
* Run ```main``` or ```./main```, providing the following parameters:
    * number of the test function (see ```equations.hpp``` file):
        [ 1, 2, 3, 4, 5, 6 ]
	* solver identification code:
        [ FE, Heun, RK4, IserNor, RK, adapFE, adapHeun, adapRK4, adapIserNor,
        adapRK ]
* Optional parameters:
    * initial step [ any double, default 0.1 ]
    * tolerance [ any double, default 0.01 ]
* Note that the inital step needs not be an even divisor of the time interval;
    if it's not, the last step will be shortened so as to fit the remaining time
* To execute the IserNor method in parallel (either the adaptive version or the
    regular one), include ```mpiexec -np 2``` when calling ```main```
* After running, information about the equation solved will appear on screen
* The solution and time instants will be saved in
    ```solution\_<#test>\_\<method>.txt```
* Run with Matlab the ```check_solutions.m``` script directly from the
    ```test``` subfolder selecting the number of the test to see a plot of exact
    vs computed solution
* Run on the terminal the ```time.sh``` script directly from the ```test```
    subfolder to compare time executions of both the sequential and the parallel
    version of the IserNor method on the tests number 4, 5, and 6. Information
    will be saved into the ```timeres.txt``` file

### Examples
* ```./main 3 RK 0.2 1e-3```
* ```./main 2 adapFE```
* ```mpiexec -np 2 ./main 4 IserNor```
* ```mpiexec -np 2 ./main 6 adapIserNor```

### Adding new equations
1) Add a new EquationFunction in the ```equations.cpp``` and ```equations.hpp```
    files
2) In function ```initialize_data``` inside the ```RuntimeUtils.cpp``` file,
    add the specifications of the new test

### Adding new Runge-Kutta methods
* To introduce a new Runge-Kutta method exploiting the RK or adapRK classes,
    it is enough to provide the appropriate Butcher tableau in the
    ```initialize_solver``` function inside the ```RuntimeUtils.cpp``` file
    (default values are the ones for FE and adapHeun, respectively)
