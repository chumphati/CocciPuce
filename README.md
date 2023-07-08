# CocciPuce

Population simulation of ladybirds and aphids. M1 C programming project.

## Launch the simulation

Once the project has been cloned and placed in the coccipuce directory, 2 methods are possible: <br/>

### Method 1: launch from command line in a terminal

The command line is :<br/>

    gcc -Wall model/coccinelle.c model/direction.c model/potager.c model/puceron.c model/tomato.c ui/cui.c ui/manager.c initialization.c rule.c simulation.c main.c -o executable
    ./executable

### Method 2: using the makefile

The commands needed to launch the entire project are :<br/>

    make all
    make launch
