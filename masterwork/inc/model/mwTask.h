#pragma once
#include "model/mwModelItem.h"
#include <string>
#include <ctime>

class mwTask : public mwModelItem
{
public:
	mwTask(std::string name, std::string dec);
	mwTask();
	~mwTask();
	void StampCreationTime();
	void SetProjectId(int id);
	std::string task_name;
	std::string task_description;
	std::time_t task_creation_time;
	int project_id;
};

