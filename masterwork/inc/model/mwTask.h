#pragma once
#include "model/mwModelItem.h"
#include <string>

class mwTask : public mwModelItem
{
public:
	mwTask(std::string name, std::string dec);
	mwTask();
	~mwTask();
private:
	std::string task_name;
	std::string task_description;
};

