#include "model/mwTask.h"

mwTask::mwTask()
{
}

mwTask::~mwTask()
{
}

mwTask::mwTask(std::string name, std::string dec)
{
	task_name = name;
	task_description = dec;
}
