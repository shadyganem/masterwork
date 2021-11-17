#pragma once

#include "model/mwModelItem.h"
#include "model/mwDBHandler.h"
#include "model/mwTask.h"
#include "model/mwProject.h"
#include "model/mwUser.h"

#include <string>

class mwModel
{
public:
	mwModel();
	void SetDbPath(std::string path);
	bool InitModel();
	bool AddUser(mwUser& user);
	bool AddProject(mwProject& project);
	bool AddTask(mwTask& task);
private:
	bool InitUsersTable();
	bool InitProjectsTable();
	bool InitTasksTable();
	std::string m_db_path;
	mwDBHandler m_db_handler;
	bool is_initialized;
};

