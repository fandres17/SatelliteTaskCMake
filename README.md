# SatelliteTaskCMake
Satellite tasking simulation with 2 satellites and a terrain station. 
The input of the system is a txt file with different tasks, each task contanining a number of resources and payoff. This tasks have to be assigned by the terrain station to the satellites taking into account that if a resource is being used by the satellite, then no other task that uses the same resource should be assigned to the satellite. Each task contains a payoff which is a number indicating the benefit of executing it. The goal for the terraing station is to maximize payoff in the assignation of tasks.

## Structure
``` text
.
├── CMakeLists.txt
├── include
│   ├── ISatellite.h
│   ├── ITerrainStation.h
│   ├── Satellite.h
│   ├── Task.h
│   ├── TaskInfoTerrain.h
│   ├── TaskResult.h
│   └── TerrainStation.h
├── resources
│   ├── inputData1.txt
│   ├── test1.txt
│   ├── test2.txt
│   ├── test3.txt
│   └── test4.txt
└── src
    ├── Satellite.cpp
    ├── Source.cpp
    ├── Task.cpp
    └── TerrainStation.cpp
```


Sources go in [src/](SatelliteTask/src/), header files in [include/](SatelliteTask/include/), main function is in [Source.cpp](SatelliteTask/src/Source.cpp).
There is a folder for resoures in [resources/](SatelliteTask/resources/) which are files used as input of the Source program, please do not confuse this resources folder with the resources that each task can use. These files can be used as model to create different entries. If the program is not able to properly read a file, it will automatically try to read the example file inputData1.txt

The following is an example of tab separated input file:

``` text
fotos	2	1	5	10
mant	2	1	2	1
pruebas	2	5	6	1
fsck	2	1	6	0.1

```
The following is the structure of each line (row):<br/>
-First column is the name of the task. You can use any name in a single word.<br/>
-Second column is the number of resources that each task use.<br/>
-Third column is the number of the first resource.<br/>
-Fourth column is the number of the second resource in case the task use two resources at least.<br/>
-Fifth column is the number of the third resource in case the task use three resources at least.<br/>
-...<br/>
-Last column for each line is the payoff.<br/>

Each column is separated by a tabulation.<br/>

If you add a new executable, say `app/hello.cpp`, you only need to add the following two lines to [CMakeLists.txt](CMakeLists.txt):

``` cmake
add_executable(main app/main.cpp)   # Name of exec. and location of file.
target_link_libraries(main PRIVATE ${LIBRARY_NAME})  # Link the executable to lib built from src/*.cpp (if it uses it).
```

You can find the example source code that builds the `main` executable in [app/main.cpp](app/main.cpp) under the `Build` section in [CMakeLists.txt](CMakeLists.txt).
If the executable you made does not use the library in [src/](src), then only the first line is needed.


## Building

Clone the repository, and change directory to the folder created. Then use typical cmake commands as shown in the example:

Example:

``` bash
> git clone https://github.com/fandres17/SatelliteTaskCMake.git
> cd SatelliteTaskCmake/
> cmake .
> cmake --build .
> make test      # Makes and runs the tests.
```
## Running the executable

Once you have build the project you will be able to run the executable. The executable receive an input filename as parameter.

Example:

``` bash

> cd SatelliteTask/
> ./SatelliteTasking test2.txt
```
