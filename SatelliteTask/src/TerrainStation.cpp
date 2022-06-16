#include "../include/TerrainStation.h"

#include <iostream>
#include <map>
#include <algorithm>
#include <set>


bool TerrainStation::resourceCollide(const std::vector<int>& taskResources, const std::set<int>& satResourcesUsed) const
{
	bool result = false;
	for (int taskresource : taskResources) {
		//find if already exist in the set
		auto found=satResourcesUsed.find(taskresource);
		if (found == satResourcesUsed.end()) {
			//not found;
			result = false;
		}
		else {
			result= true;
			break;
		}
	}
	return result;
}

void TerrainStation::addResourceToHelper(const std::vector<int>& taskResources, std::set<int>& satResourcesUsed)const
{
	for (int resource : taskResources) {
		satResourcesUsed.insert(resource);
	}
}

TerrainStation::TerrainStation(std::string identifier)
{
	this->identifier = identifier;
}

void TerrainStation::addTask(const Task &taskAdded)
{
	tasksInfoToAssign.push_back({ taskAdded,0,nullptr, TaskState_t::UNASSIGNED});
}

void TerrainStation::addMultipleTasks(std::vector<Task> &tasksVector)
{
	for (Task tempTask : tasksVector) {
		this->addTask(tempTask);
	}
}

void TerrainStation::scheduleTasks() {
	//Only schedule in case there are at least 1 Satellite
	if (this->satVector.size() == 0) {
		return;
	}
	//Scores will give us the priority of the tasks to be assigned
	calculateScoresForEachTask();
	
	//Create a helper container that will make easier to check resource collision
	// this is going to be a vector with equal number of positions than satellites
	//each position is a set representing the resources used by the satellite
	std::vector<std::set<int>> helperVector;
	helperVector.resize(this->satVector.size());
	// First load tasks for satellites that are already executing a task in case we are not starting from 
	//zero task assigned to satellites
	for (int i = 0; i < tasksInfoAssigned.size(); ++i) {
		//identify satellite index
		auto found=std::find(satVector.begin(), satVector.end(), tasksInfoAssigned[i].satellite);
		if (found != satVector.end()) {
			//found
			int index = found - satVector.begin();
			addResourceToHelper(tasksInfoAssigned[i].task.resources, helperVector[i]); //i is satellite	
		}
		else {
			//not found
			std::cout << "Satellite from task not found in list"<<std::endl;
		}
	}

			/***Assign tasks to satellites*****/
	// Iterate each task to assign to find a satellite available
	for (int i = 0; i < tasksInfoToAssign.size(); ++i) {
		std::vector<int>& taskResources = tasksInfoToAssign[i].task.resources; //i represent task
																			   
		//Iterate satellites to check task collision with satellites. 
		for (int j = 0; j < helperVector.size(); ++j) {
			bool collision = resourceCollide(taskResources, helperVector[j]);	//j represent satellite
			if (!collision) {
				tasksInfoToAssign[i].satellite = this->satVector[j]; //assign satellite
				tasksInfoToAssign[i].state = TaskState_t::ASSIGNED;
				//move from taskToassign to assigned tasks
				this->tasksInfoAssigned.push_back(tasksInfoToAssign[i]); //i is task
				//update resource map
				addResourceToHelper(taskResources, helperVector[j]); //j is satellite		
				this->satVector[j]->addTask(tasksInfoToAssign[i].task, this);
				break; 
			}
		}
	}

	//Remove tasks assigned from tasktoAssign vector (they are now in taskAssigned vector)
	for (int k = tasksInfoToAssign.size()-1; k >= 0; --k) {
		if (tasksInfoToAssign[k].state == TaskState_t::ASSIGNED) {
			tasksInfoToAssign.erase(tasksInfoToAssign.begin() + k);
		}
	}
	return;
}


/*
* The idea is to find a sub-optimal solution that assign a score to each task based
* in the following ideas:
* A. It should have a better score with a higher payoff
* B. It should have a better score if the task do not use a lot of resources
* C. It should have a better score if the task is not using a popular resource
*/
void TerrainStation::calculateScoresForEachTask()
{
	//get unique resources from all tasksInfoToAssign and store them in a map with
	//resoure number as key, and resource count as value as first step to calculate score
	std::map<int, int> resourceCountmap;
	for (TaskInfoTerrain tempTaskScore : tasksInfoToAssign) {
		Task tempTask = tempTaskScore.task;
		for (int resource : tempTask.resources) {
			auto found = resourceCountmap.find(resource);
			if (found != resourceCountmap.end()) {
				//key found. get count and increment
				++(found->second);
			}
			else {
				//not found
				resourceCountmap.insert({ resource, 1 });
			}
		}
	}

	//calculate score for each Task
	for (TaskInfoTerrain& tempTaskScore : tasksInfoToAssign) {
		float scorePopularResources = 0;
		float scoreFewResources = 0;
		float scorePayoff = 0;
		for (int resource : tempTaskScore.task.resources) {
			int resourceCount = resourceCountmap[resource];
			float resourceScore = 1.0f / resourceCount;
			scorePopularResources += resourceScore;
		}
		scorePopularResources = scorePopularResources * K_POPULAR_RESOURCES;
		scoreFewResources = K_FEW_RESOURCES / tempTaskScore.task.resources.size();
		scorePayoff = (tempTaskScore.task.payoff) * K_PAYOFF;

		tempTaskScore.score = scorePopularResources * scoreFewResources * scorePayoff;

	}

	//Sort task by score using custom comparator
	std::sort(tasksInfoToAssign.begin(), tasksInfoToAssign.end(),
		[](const TaskInfoTerrain& leftObj, const TaskInfoTerrain& rightObj) {
			return leftObj.score > rightObj.score; });
}

void TerrainStation::taskResult(TaskResult taskResult)
{
	//	This method implement a mutex as multiple sattelites could answer at the same time
	{
	std::lock_guard<std::mutex> mutex1(mtx);
	if (taskResult.executed) {
		std::cout << "Task : " << taskResult.task.name << " successfully executed"<<std::endl;
	}
	else {
		std::cout << "Task : " << taskResult.task.name << " failed" << std::endl;
	}

	//this code below is not part of the requirements but would be normal for a continuous
	// operation of the terrain station
	//find assigned task
	for (int i = 0; i < tasksInfoAssigned.size(); ++i) {
		if (tasksInfoAssigned[i].task.name == taskResult.task.name) {
			if (taskResult.executed) {
				//task completed so remove from taskAssigned vector in case there are tasks
				//waiting for resources
				tasksInfoAssigned.erase(tasksInfoAssigned.begin() + i);
			}
			else {
				//task failed so relocate in task to assing for a future reescheduling
				//and remove from taskAssigned vector
				tasksInfoToAssign.push_back(tasksInfoAssigned[i]);
				tasksInfoAssigned.erase(tasksInfoAssigned.begin() + i);
			}

		}
	}
		//this->scheduleTasks(); //This would be normal but is not part of the requirements
	}


}

void TerrainStation::addSatellite(ISatellite* sat)
{
	satVector.push_back(sat);
}



