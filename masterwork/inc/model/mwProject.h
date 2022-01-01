#pragma once
#include "model/mwModelItem.h"
#include <string>
#include <ctime>

class mwProject : public mwModelItem
{
public:
	enum ProjectStatus
	{
		DELETED = -1,
		DEFAULT
	};

public:
	mwProject();
	mwProject(std::string name);
	~mwProject();
	void ChangeName(std::string new_name);
	std::time_t start_time;
	std::string name;
	int uid;
	int user_uid;
	int status;
	bool is_active;
	void StampCreationTime();
};
