#include "model/mwProject.h"

mwProject::mwProject()
{
	project_name = "New Project";
	std::time(&project_cration_time);
}

mwProject::mwProject(std::string name)
{
	this->project_name = name;
	std::time(&this->project_cration_time);
}

mwProject::~mwProject()
{
}
