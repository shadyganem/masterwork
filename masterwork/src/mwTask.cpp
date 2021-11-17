#include "model/mwTask.h"

mwTask::mwTask()
{
	name = "New Task";
	std::time(&start_time);
	project_uid = 0;
}

mwTask::~mwTask()
{
}

void mwTask::StampCreationTime()
{
	std::time(&start_time);
}

void mwTask::SetProjectId(int id)
{
	project_uid = id;
}

mwTask::mwTask(std::string task_name, std::string task_description)
{
	name = task_name;
	description = task_description;
	project_uid = 0;
	std::time(&start_time);
}
