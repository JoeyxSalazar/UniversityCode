This was my first take home final for ECE 322 (Systems Programming) which includes 
two shell scripts and a .c file

The create project script creates a directory with a bin folder and a src folder. It then copies itself into this directory

The build project script is placed within the bin directory, moves to source, compiles all of the code, then returns an executable into the bin

The myfind.c code will search any given path and its subdirectories for instances given in argv[2]
    for example
    myfind /home/students/jes409/FourthSemester/ myls
    would return any instances of "myls" found within the given path
