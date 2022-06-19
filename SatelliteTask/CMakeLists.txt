# CMakeList.txt : CMake project for SatelliteTaskCMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Add source to this project's executables.
add_executable (SatelliteTasking    "include/ISatellite.h" "include/ITerrainStation.h" "src/Satellite.cpp" "include/Satellite.h" "src/Source.cpp" "src/Task.cpp"   "include/TaskInfoTerrain.h"  "include/TaskResult.h" "src/TerrainStation.cpp" "include/TerrainStation.h" "include/Task.h" )

#this flags are required by gcc
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -pthread")
string(APPEND CMAKE_EXE_LINKER_FLAGS "-lpthread")

# TODO: Add tests and install targets if needed.
add_custom_command(TARGET SatelliteTasking POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/SatelliteTask/resources/ $<TARGET_FILE_DIR:SatelliteTasking>
)
install(TARGETS SatelliteTasking DESTINATION /bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/SatelliteTask/resources/
		DESTINATION /bin/resources		
)



enable_testing()

#The following tests are related with some given input files
#The test will pass if the tasks that maximize the payoff are assigned to satellites, so
#they will appear in the std output when performig a regex search
#The task that were not assigned will not appear in the std output so the test will
#fail if those tasks are found in a regex search
add_test(NAME Test0 COMMAND SatelliteTasking inputData1.txt)
set_tests_properties(
	Test0
	PROPERTIES 
	PASS_REGULAR_EXPRESSION "fotos"
	PASS_REGULAR_EXPRESSION "mantenimiento"
	PASS_REGULAR_EXPRESSION "pruebas"
	FAIL_REGULAR_EXPRESSION "fsck"
)

add_test(NAME Test1 COMMAND SatelliteTasking test2.txt)
set_tests_properties(
	Test1
	PROPERTIES 
	PASS_REGULAR_EXPRESSION "fotos"
	PASS_REGULAR_EXPRESSION "fsck"
	FAIL_REGULAR_EXPRESSION "pruebas"
	FAIL_REGULAR_EXPRESSION "mantenimiento"
)

add_test(NAME Test2 COMMAND SatelliteTasking test2.txt)
set_tests_properties(
	Test2
	PROPERTIES 
	PASS_REGULAR_EXPRESSION "fotos"
	PASS_REGULAR_EXPRESSION "fsck"
	FAIL_REGULAR_EXPRESSION "pruebas"
	FAIL_REGULAR_EXPRESSION "mantenimiento"
)

add_test(NAME Test3 COMMAND SatelliteTasking test3.txt)
set_tests_properties(
	Test3
	PROPERTIES 
	PASS_REGULAR_EXPRESSION "medir"
	PASS_REGULAR_EXPRESSION "comunicar"
	PASS_REGULAR_EXPRESSION "diagnosticar"
	PASS_REGULAR_EXPRESSION "actualizar"
	FAIL_REGULAR_EXPRESSION "reparar"
)

add_test(NAME Test4 COMMAND SatelliteTasking test4.txt)
set_tests_properties(
	Test4
	PROPERTIES 
	PASS_REGULAR_EXPRESSION "Autodiagnostico"
	PASS_REGULAR_EXPRESSION "Fotografiar"
	PASS_REGULAR_EXPRESSION "Transmitir"
	PASS_REGULAR_EXPRESSION "Explorar"
	PASS_REGULAR_EXPRESSION "Espiar"
	FAIL_REGULAR_EXPRESSION "Conectar"
	FAIL_REGULAR_EXPRESSION "Matenimiento"
	FAIL_REGULAR_EXPRESSION "Suspension"
)
