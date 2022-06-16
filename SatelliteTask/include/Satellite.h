#pragma once

#include "Task.h"
#include "ISatellite.h"
#include <string>
#include <thread>
#include <deque>
#include <mutex>


class TaskCallback {
public:
	Task task;
	ITerrainStation* terrainRef;
};


class Satellite : ISatellite
{
private:
	std::deque<TaskCallback> taskQueue;
	std::mutex mtx;
	void processTask(const TaskCallback& taskRef)const;
	bool satelliteAlive{true};

public:
	std::thread satelliteThread;
	std::string identifier;
	Satellite(std::string);
	void addTask(Task taskToAdd,  ITerrainStation* terrainRef)override;
	void endSatelliteTask();
	~Satellite();
};



