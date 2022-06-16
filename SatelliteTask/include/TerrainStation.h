#pragma once


#include "ITerrainStation.h"
#include "ISatellite.h"
#include "Task.h"
#include "TaskResult.h"
#include "TaskInfoTerrain.h"
#include <vector>
#include <deque>
#include <set>


class TerrainStation : ITerrainStation
{
private:
	std::vector<ISatellite*> satVector;
	std::deque<TaskResult> tasKresults;
	std::vector<TaskInfoTerrain> tasksInfoToAssign; //this vector for task pending to be scheduled
	std::vector<TaskInfoTerrain> tasksInfoAssigned; //this vector for scheduled tasks
	std::mutex mtx;
	const float K_FEW_RESOURCES = 1.0;
	const float K_POPULAR_RESOURCES = 1.0;
	const float K_PAYOFF = 1.0;
	bool resourceCollide(const std::vector<int>& taskResources, const std::set<int>& satResourcesUsed) const;
	void addResourceToHelper(const std::vector<int>& taskResources, std::set<int>& satResourcesUsed)const;
	void calculateScoresForEachTask();

public:
	std::string identifier;
	TerrainStation(std::string);
	void addTask(const Task & taskAdded)override;
	void addMultipleTasks(std::vector<Task> & tasksVector)override;
	void scheduleTasks()override;

	void taskResult(TaskResult taskResult)override;
	void addSatellite(ISatellite* sat)override;


};

