# CMakeList.txt : CMake project for SatelliteTaskCMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Add source to this project's executables.
add_executable (SatelliteTasking  "SatelliteTaskCMake.h" "ISatellite.cpp" "ISatellite.h" "ITerrainStation.h" "Satellite.cpp" "Satellite.h" "Source.cpp" "Task.cpp" "Task.h"  "TaskInfoTerrain.h" "TaskResult.cpp" "TaskResult.h" "TerrainStation.cpp" "TerrainStation.h")

# TODO: Add tests and install targets if needed.
