#include "model/mwTask.h"

mwTask::mwTask()
{
	name = "New Task";
	std::time(&start_time);
	project_uid = 0;
	status = TaskStatus::NOTSTARTED;
	priority = TaskPriority::MEDIUM;
	deadline = 0;
	parent_uid = 0;
}

mwTask::~mwTask()
{
	name = "New Task";
	std::time(&start_time);
	project_uid = 0;
	status = TaskStatus::NOTSTARTED;
	priority = TaskPriority::MEDIUM;
	deadline = 0;
	parent_uid = 0;
}

void mwTask::StampCreationTime()
{
	std::time(&start_time);
}

void mwTask::SetProjectId(int id)
{
	project_uid = id;
}

std::string mwTask::GetStatus()
{
	std::string status;
	switch(this->status)
	{
	case TaskStatus::NOTSTARTED:
		status = "Not Started";
		break;
	case TaskStatus::DONE:
		status = "Done";
		break;
	case TaskStatus::WIP:
		status = "WIP";
		break;
	case TaskStatus::CANCELED:
		status = "Canceled";
		break;
	case TaskStatus::BLOCKED:
		status = "Blocked";
		break;
	default:
		status = "N/A";
		break;
	}
	return status;
}

std::string mwTask::GetPriority()
{
	std::string priority;
	switch (this->status)
	{
	case TaskPriority::HIGH:
		priority = "High";
		break;
	case TaskPriority::MEDIUM:
		priority = "Meduim";
		break;
	case TaskPriority::LOW:
		priority = "Low";
		break;
	case TaskPriority::SHOWSTOPPER:
		priority = "Show Stopper";
		break;
	default:
		priority = "N/A";
		break;
	}
	return priority;
}

mwTask::mwTask(std::string task_name, std::string task_description)
{
	name = task_name;
	description = task_description;
	project_uid = 0;
	std::time(&start_time);
}
