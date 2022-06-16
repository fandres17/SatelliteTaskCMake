#include "Task.h"
#include <iostream>



Task::Task(std::string name, std::vector<int> resources, float payoff)
{
	
	this->name = name;
	this->payoff = payoff;
	this->resources = resources;
	
}

std::ostream& operator<<(std::ostream& out, const Task& task)
{
	out <<"task: "<< task.name << " payoff:" << task.payoff;
	out << " resources: ";
	for (auto resource : task.resources) {
		out << resource << " ";
	}
	return out;
}
