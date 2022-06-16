#include "include/Satellite.h"
#include "include/ISatellite.h"
#include "include/Task.h"
#include "include/TerrainStation.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


std::vector<Task> tasksToAssign;


void readTasksFromFile(std::string &filename);

int main(int argc, char** argv) {
	std::string inFile;
	if (argc == 2) {
		inFile = argv[1];
	}
	else {
		std::cout << "Filename not detected. ";
		std::cout << "Usage: SatelliteTasking filename" << std::endl;
		std::cout << "Using default input file...";
		inFile = "inputData1.txt";
	}
	using namespace std::string_literals;
	using namespace std::chrono_literals;
	
	//Read input from file
	try {
		readTasksFromFile(inFile);
	}
	catch(std::runtime_error &error){
		std::cout << error.what() << std::endl;
		return -1;
	}

	TerrainStation terrainStation(R"(Terr1)"s);
	ITerrainStation* iTerrainStation = (ITerrainStation*)&terrainStation;
	iTerrainStation->addMultipleTasks(tasksToAssign);

	Satellite sat1(R"(Sat1)"s);
	Satellite sat2(R"(Sat2)"s);
	iTerrainStation->addSatellite((ISatellite*)&sat1);
	iTerrainStation->addSatellite((ISatellite*)&sat2);
	iTerrainStation->scheduleTasks();


	std::this_thread::sleep_for(2000ms); //simulate some delay in the execution of tasks
	
	/*End program*/
	std::cout << std::endl;
	std::cout << "Terminating program execution" << std::endl;
	sat1.endSatelliteTask();
	sat2.endSatelliteTask();
	sat2.satelliteThread.join();
	sat1.satelliteThread.join();
	return 0;
}


void readTasksFromFile(std::string &filename) {

	std::ifstream input{ filename };
	//std::ifstream input{ "inputData1.txt" };
	if (input.fail()) {	
		throw std::runtime_error("Could not open/locate file with input tasks");
	}
	while (!input.eof()) {
		std::string line;
		std::getline(input, line);
		if (line.empty()) {
			continue; //empty line
		}
		std::istringstream lineStream(line);

		std::string nombre;
		lineStream >> nombre;
		int sizeArray = 0;
		lineStream >> sizeArray;
		std::vector<int> resoures;
		for (int i = 0; i < sizeArray; ++i) {
			int temp = 0;
			lineStream >> temp;
			resoures.push_back(temp);
		}
		float payoff;
		lineStream >> payoff;
		Task temp(nombre, resoures, payoff);
		tasksToAssign.push_back(temp);
	}


	if (input.eof()) {
		std::cout << "File " <<filename<<" was read." <<std::endl;
		std::cout << std::endl;
	}	
	input.close();
	
}
