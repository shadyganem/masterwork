#pragma once

#include "model/mwModelItem.h"
#include "model/mwDBHandler.h"
#include "model/mwTask.h"
#include "model/mwProject.h"
#include "model/mwUser.h"

#include <string>
#include <vector>
#include <mutex>


class mwModel
{
public:
	mwModel();
	void SetDbPath(std::string path);
	bool InitModel();
	bool AddUser(mwUser& user);
	bool AddProject(mwProject& project);
	bool AddTask(mwTask& task);
	bool GetActiveUser(mwUser& user);
	bool SetActiveUser(mwUser& user);
	bool GetAllUsers(std::vector<mwUser>& ret_users_vect);
	bool GetActiveProject(mwProject& project, mwUser& user);
	bool GetAllProjects(std::vector<mwProject>& prjects_vect, const mwUser& currnet_user);
	bool SetActiveProject(mwProject& project);
	bool GetProjectTasks(mwProject& project,  std::vector<mwTask>& ret_tasks_vect);
private:
	bool ConnectDb();
	bool DisconnectDb();
	bool InitUsersTable();
	bool InitProjectsTable();
	bool InitTasksTable();
	bool InitNotificationsTable();
	std::string m_db_path;
	mwDBHandler m_db_handler;
	bool is_initialized;
	std::mutex m_mutex;
};

