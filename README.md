# Adaptive Numerical Solvers for ODEs
## Instructions
You will need a terminal to run the following commands.

### Downloading from GitHub
* Run ```git clone https://github.com/poliprojects/apc-project.git```

### Installing
* Compile by running ```make```

### Documentation
* Produce documentation by running ```doxygen```
* ```docs``` subfolder will appear that contains documentation in both LaTex and
    HTML forms

### Usage
* Run ```main``` or ```./main```, providing the following parameters:
    * number of the test function (see ```equations.hpp``` file):
        [ 1, 2, 3, 4, 5, 6, 7, 8 ]
	* solver identification code:
        [ FE, Heun, RK4, IserNor, RK, adapFE, adapHeun, adapRK4, adapIserNor,
        adapRK ]
* Optional parameters:
    * initial step [ positive double, default 0.1 ]
    * tolerance, maximum error in adaptive methods
      [ positive double, default 0.01 ]
    * minimum step size in adaptive methods [ positive double, default 0.005 ]
    * maximum step size in implicit adaptive methods
      [ positive double, default 0.5 ]
* Running the program will display a summary of the problem data and of the
    solver parameters, as well as the execution time
* Note that the inital step needs not be an even divisor of the time interval;
    if it's not, the last step will be shortened so as to fit the remaining time
* To execute the IserNor method in parallel (either the adaptive version or the
    regular one), include ```mpiexec -np 2``` when calling ```main```
* After running, information about the equation solved will appear on screen
* The solution and time instants will be saved in
    ```solution_<#test>_<method>.txt```
* Run with Matlab the ```check_solutions.m``` script directly from the
    ```test``` subfolder selecting the number of the test to see a plot of exact
    vs computed solution, as well as produce a plot for the mean square error
    (the corresponding solution txt file is needed in the root folder)
* Run on the terminal the ```time.sh``` script directly from the ```test```
    subfolder to compare time executions of both the sequential and the parallel
    version of the IserNor method on the tests number 4, 5, and 6. Information
    will be saved into the ```timeres.txt``` file
* Run on the terminal the ```testing_suite.sh``` script directly from the
    ```test``` subfolder to execute the program with all available combinations
    of solvers and example functions. The results will be saved in the
    respective usual files

### Examples
* ```./main 3 RK 0.2 1e-3```
* ```./main 2 adapFE```
* ```mpiexec -np 2 ./main 4 IserNor```
* ```mpiexec -np 2 ./main 6 adapIserNor```

## Customization
### Adding new equations
* Add a new EquationFunction in the ```equations.cpp``` and ```equations.hpp```
    files
* In function ```initialize_data``` inside the ```RuntimeUtils.cpp``` file,
    add the specifications of the new test
* In function ```check_input_parameters``` inside the ```RuntimeUtils.cpp```
    file, increase the value of ```n_tests``` by 1

### Adding new Runge-Kutta methods
* To introduce a new Runge-Kutta method exploiting the RK or adapRK classes,
    it is enough to provide the appropriate Butcher tableau in the
    ```initialize_solver``` function inside the ```RuntimeUtils.cpp``` file
    (default values are the ones for FE and adapHeun, respectively)
