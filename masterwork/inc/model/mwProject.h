#pragma once
#include "model/mwModelItem.h"
#include <string>
#include <ctime>
class mwProject : public mwModelItem
{
public:
	mwProject();
	mwProject(std::string name);
	~mwProject();
	void ChangeName(std::string new_name);
	std::time_t start_time;
	std::string name;
	int uid;
	int user_uid;
	bool is_active;
	void StampCreationTime();
};
