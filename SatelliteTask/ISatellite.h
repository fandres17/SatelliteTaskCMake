#pragma once
#include "Task.h"

class ITerrainStation;

class ISatellite
{
public:
	virtual void addTask(Task taskToAdd,  ITerrainStation *terrainRef)=0;
	virtual ~ISatellite(){};
};

