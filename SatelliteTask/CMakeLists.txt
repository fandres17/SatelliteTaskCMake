# CMakeList.txt : CMake project for SatelliteTaskCMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Add source to this project's executables.
add_executable (SatelliteTasking  "SatelliteTaskCMake.h"  "include/ISatellite.h" "include/ITerrainStation.h" "src/Satellite.cpp" "include/Satellite.h" "src/Source.cpp" "src/Task.cpp"   "include/TaskInfoTerrain.h"  "include/TaskResult.h" "src/TerrainStation.cpp" "include/TerrainStation.h" "include/Task.h" "Tester.cpp")

# TODO: Add tests and install targets if needed.
add_custom_command(TARGET SatelliteTasking POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/SatelliteTask/resources/ $<TARGET_FILE_DIR:SatelliteTasking>
)

enable_testing()

add_test(NAME Test0 COMMAND SatelliteTasking)
set_tests_properties(
	Test0
	PROPERTIES PASS_REGULAR_EXPRESSION "Task added to Sat1<--- task: fotos payoff:10 resources: 1 5 [\r
	\n\t]*Task added to Sat2<--- task: mantenimiento payoff:1 resources: 1 2 [\r
	\n\t]*Task added to Sat2<--- task: pruebas payoff:1 resources: 5 6 "
)

add_test(NAME Test1 COMMAND SatelliteTasking test1.txt)
set_tests_properties(
	Test1
	PROPERTIES PASS_REGULAR_EXPRESSION "Task"
)
