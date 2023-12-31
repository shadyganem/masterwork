#include "model/Task.h"
#define _CRT_SECURE_NO_WARNINGS

mw::Task::Task()
{
	name = "New Task";
	std::time(&start_time);
	project_uid = 0;
	status = TaskStatus::NOTSTARTED;
	priority = TaskPriority::MEDIUM;
	deadline = 0;
	parent_uid = 0;
	this->notification_enabled = true;
}

mw::Task::~Task()
{
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

std::string mw::Task::GetLastUpdate()
{
	// Convert the epoch timestamp to a struct tm
	std::tm timeinfo;


	#ifdef _WIN32
		localtime_s(&timeinfo, &this->last_update);
	#else
		localtime_r(&now, &localTime);

	#endif
	// Format the date and time as a string
	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeinfo);
	std::string last_update = buffer;
	return last_update;
}

std::string mw::Task::GetEndTime()
{

	// Convert the epoch timestamp to a struct tm
	std::tm timeinfo;


	#ifdef _WIN32
		localtime_s(&timeinfo, &this->end_time);
	#else
		localtime_r(&now, &localTime);

	#endif

	// Format the date and time as a string
	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeinfo);
	std::string end_time = buffer;
	return end_time;
}

std::string mw::Task::GetDeadline()
{
	return this->ConvertTimeToString(this->deadline);
}

mw::Task::Task(std::string task_name, std::string task_description)
{
	name = task_name;
	description = task_description;
	project_uid = 0;
	std::time(&start_time);
	std::time(&last_update);
	this->notification_enabled = true;
}
