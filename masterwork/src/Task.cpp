#include "model/Task.h"

mw::Task::Task()
{
	name = "New Task";
	std::time(&start_time);
	project_uid = 0;
	status = TaskStatus::NOTSTARTED;
	priority = TaskPriority::MEDIUM;
	deadline = 0;
	parent_uid = 0;
}

mw::Task::~Task()
{
	name = "New Task";
	std::time(&start_time);
	std::time(&last_update);
	project_uid = 0;
	status = TaskStatus::NOTSTARTED;
	priority = TaskPriority::MEDIUM;
	deadline = 0;
	parent_uid = 0;
}

void mw::Task::StampCreationTime()
{
	std::time(&start_time);
}

void mw::Task::StampLastUpdateTime()
{
	std::time(&last_update);
}

void mw::Task::StampEndTime()
{
	std::time(&end_time);
}

void mw::Task::SetProjectId(int id)
{
	project_uid = id;
}

std::string mw::Task::GetStatus()
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

std::string mw::Task::GetPriority()
{
	std::string priority;
	switch (this->priority)
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

mw::Task::Task(std::string task_name, std::string task_description)
{
	name = task_name;
	description = task_description;
	project_uid = 0;
	std::time(&start_time);
	std::time(&last_update);
}
