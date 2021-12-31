#include "model/mwProject.h"

mwProject::mwProject()
{
	this->name = "New Project";
	this->status = 0;
	std::time(&this->start_time);
}

mwProject::mwProject(std::string name)
{
	this->name = name;
	this->status = 0;
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
