#include "../include/Satellite.h"
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include "../include/ITerrainStation.h"




void Satellite::processTask(const TaskCallback& taskRef)const
{
	//generate randon number between 1 and 10
	int random=rand() % 10 + 1;
	bool taskExecutedSuccessfully = false;
	if (random > 2) {
		taskExecutedSuccessfully = true;
	}
	TaskResult tr{ taskRef.task,taskExecutedSuccessfully };
	if (taskRef.terrainRef != nullptr) {
		(taskRef.terrainRef)->taskResult(tr);
	}
	else {
		throw std::runtime_error("Satellite reference not found");
	}
	
}

Satellite::Satellite(std::string identifier ){
	this->identifier = identifier;
	auto satelliteTask = [this]() {
		srand(time(0)); // Use current time as seed for random generator
		using namespace std::chrono_literals;
		while(satelliteAlive){
			std::this_thread::sleep_for(50ms);
			std::lock_guard<std::mutex> mutex1(mtx);
			if(!taskQueue.empty()){
			TaskCallback tempTcbk = taskQueue.front();
			taskQueue.pop_front();
			//std::cout << "Processing task: " << tempTcbk.task.name<<std::endl;
			processTask(tempTcbk);
			}

		}
	};
	//Starts the execution of the Thread
	satelliteThread = std::thread(satelliteTask);
}


void Satellite::addTask(Task taskToAdd,  ITerrainStation* terrainRef){
	std::cout << "Task added to " << this->identifier <<"<--- "<< taskToAdd <<std::endl;
	//Provide a mutex to avoid race condition and to allow the task to wait if there are
	//not tasks added
	std::lock_guard<std::mutex> mutex1(mtx);
	TaskCallback tcb{taskToAdd,terrainRef};
	this->taskQueue.push_back(tcb);
}

void Satellite::endSatelliteTask()
{
	this->satelliteAlive = false;
}

Satellite::~Satellite()
{
}
