#pragma once
#include "Task.h"
#include "Satellite.h"
struct TaskInfoTerrain {
	Task task;
	float score;
	ISatellite* satellite;
	TaskState_t state;
};

