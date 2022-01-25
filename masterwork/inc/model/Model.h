#pragma once

#include "model/mwModelItem.h"
#include "model/mwDBHandler.h"
#include "model/Task.h"
#include "model/mwProject.h"
#include "model/User.h"

#include <string>
#include <vector>
#include <mutex>


class Model
{
public:
	Model();
	void SetDbPath(std::string path);
	bool InitModel();
	bool AddUser(mw::User& user);
	bool AddProject(mwProject& project);
	bool AddTask(mw::Task& task);
	bool GetActiveUser(mw::User& user);
	bool SetActiveUser(mw::User& user);
	bool DeleteTask(mw::Task& task);
	bool DeleteProject(mwProject& project);
	bool GetAllUsers(std::vector<mw::User>& ret_users_vect);
	bool GetActiveProject(mwProject& project, mw::User& user);
	bool GetAllProjects(std::vector<mwProject>& prjects_vect, const mw::User& currnet_user);
	bool SetActiveProject(mwProject& project);
	bool GetProjectTasks(mwProject& project,  std::vector<mw::Task>& ret_tasks_vect);
	bool GetAllTasks(std::vector<mw::Task>& tasks, mwProject& current_project);
	bool GetArchiveAllTasks(std::vector<mw::Task>& tasks, mwProject& current_project);
	bool IsTaskFound(mw::Task& task);
	bool IsProjectFound(mwProject& project);
	bool IsUserFound(mw::User& user);
	bool UpdateTask(mw::Task& task);
	bool UpdateProject(mwProject& project);
	bool UpdateUser(mw::User& user);

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

