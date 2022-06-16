#pragma once

#include <string>
#include <vector>

struct Task
{
	std::string name;
	std::vector<int> resources;
	float payoff;
	Task(std::string name, std::vector<int> resources, float payoff);
};


std::ostream& operator<<(std::ostream& out, const Task& task);


enum class TaskState_t {UNASSIGNED,ASSIGNED, EXECUTED, FAILED};


