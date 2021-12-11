#include "model/mwProject.h"

mwProject::mwProject()
{
	name = "New Project";
	std::time(&this->start_time);
}

mwProject::mwProject(std::string name)
{
	this->name = name;
	std::time(&this->start_time);
}

mwProject::~mwProject()
{
}

void mwProject::ChangeName(std::string new_name)
{
	this->name = new_name;
}

void mwProject::StampCreationTime()
{
	std::time(&this->start_time);
}
