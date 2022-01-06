#pragma once
#include "model/mwModelItem.h"
#include <string>
#include <sstream>
#include <ctime>


class mwTask : public mwModelItem
{
public:

	enum TaskStatus
	{
		NOTSTARTED,
		WIP,
		CANCELED,
		DONE,
		BLOCKED,
		DELETED = -1
	};

	enum TaskPriority
	{
		HIGH,
		MEDIUM,
		LOW,
		SHOWSTOPPER
	};

public:
	mwTask(std::string name, std::string dec);
	mwTask();
	~mwTask();
	void StampCreationTime();
	void SetProjectId(int id);
	std::string GetStatus();
	std::string GetPriority();

	int uid;
	int parent_uid;
	std::string name;
	std::string description;
	int status;
	int priority;
	std::time_t start_time;
	std::time_t end_time;
	std::time_t deadline;
	int project_uid;
	int red;
	int green;
	int blue;


};

