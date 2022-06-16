#pragma once
#include "TaskResult.h"
#include "ISatellite.h"

class ITerrainStation {

public:
	virtual void addTask(const Task& taskAdded) = 0;
	virtual void addMultipleTasks(std::vector<Task>& tasksVector)=0;
	virtual void addSatellite(ISatellite* sat)=0;
	virtual void scheduleTasks()=0;
	virtual void taskResult(TaskResult taskResult)=0;
	virtual ~ITerrainStation() {};
};