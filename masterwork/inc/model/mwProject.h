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
	std::string project_name;
	std::time_t project_cration_time;
	void StampCreationTime();
};
