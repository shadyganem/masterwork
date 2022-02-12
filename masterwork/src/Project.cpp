#include "model/Project.h"

mw::Project::Project()
{
	this->status = 0;
	std::time(&this->start_time);
}

mw::Project::Project(std::string name)
{
	this->name = name;
	this->status = 0;
	std::time(&this->start_time);
}

mw::Project::~Project()
{
}

void mw::Project::ChangeName(std::string new_name)
{
	this->name = new_name;
}

void mw::Project::StampCreationTime()
{
	std::time(&this->start_time);
}
