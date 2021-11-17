#include "model/mwTask.h"

mwTask::mwTask()
{
	task_name = "New Task";
	std::time(&task_creation_time);
}

mwTask::~mwTask()
{
}

void mwTask::StampCreationTime()
{
	std::time(&task_creation_time);
}

void mwTask::SetProjectId(int id)
{
	project_id = id;
}

mwTask::mwTask(std::string name, std::string dec)
{
	task_name = name;
	task_description = dec;
	std::time(&task_creation_time);
}
