# CMakeList.txt : CMake project for SatelliteTaskCMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Add source to this project's executables.
add_executable (SatelliteTasking  "SatelliteTaskCMake.h"  "include/ISatellite.h" "include/ITerrainStation.h" "Satellite.cpp" "include/Satellite.h" "Source.cpp" "Task.cpp" "Task.h"  "include/TaskInfoTerrain.h"  "include/TaskResult.h" "TerrainStation.cpp" "include/TerrainStation.h" "include/Task.h")

# TODO: Add tests and install targets if needed.
add_custom_command(TARGET SatelliteTasking POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/SatelliteTask/resources/ $<TARGET_FILE_DIR:SatelliteTasking>
)