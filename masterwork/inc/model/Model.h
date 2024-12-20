#pragma once

#include "model/ModelItem.h"
#include "model/DatabaseHandler.h"
#include "model/SqlStatement.h"
#include "model/Task.h"
#include "model/Project.h"
#include "model/Reminder.h"
#include "model/User.h"
#include "model/Password.h"
#include <string>
#include <vector>
#include <mutex>


class Model
{
public:
	Model();
	void SetDatabasePath(std::string path);
	bool InitModel();
	bool AddUser(mw::User& user);
	bool AddProject(mw::Project& project);
	bool AddTask(mw::Task& task);
	bool AddReminder(mw::Reminder& reminder);
	bool AddPassword(mw::Password& password);
	bool GetActiveUser(mw::User& user);
	bool SetActiveUser(mw::User& user);
	bool DeleteTask(mw::Task& task);
	bool DeleteReminder(mw::Reminder& reminder);
	bool DeletePassword(mw::Password& password);
	bool ArchiveTask(mw::Task& task);
	bool UnarchiveTask(mw::Task& task);
	bool DeleteProject(mw::Project& project);
	bool GetAllUsers(std::vector<mw::User>& ret_users_vect);
	bool GetActiveProject(mw::Project& project, mw::User& user);
	bool GetAllProjects(std::vector<mw::Project>& prjects_vect, const mw::User& currnet_user);
	bool GetAllReminders(std::vector<mw::Reminder>& reminders, const mw::User& current_user);
	bool GetAllPasswords(std::vector<mw::Password>& passwords, const mw::User& currnet_user);
	bool SetActiveProject(mw::Project& project);
	bool GetAllTasks(std::vector<mw::Task>& tasks, mw::Project& current_project);
	bool GetArchiveAllTasks(std::vector<mw::Task>& tasks, mw::Project& current_project);
	bool GetArchiveAllTasks(std::vector<mw::Task>& tasks, mw::Project& current_project, unsigned int num_of_days_ago);
	bool IsTaskFound(mw::Task& task);
	bool IsProjectFound(mw::Project& project);
	bool IsUserFound(mw::User& user);
	bool UpdateTask(mw::Task& task);
	bool UpdateProject(mw::Project& project);
	bool UpdateUser(mw::User& user);
	bool UpdateReminder(mw::Reminder& reminder);


private:
	bool ConnectDataBase();
	bool DisconnectDb();
	bool InitUsersTable();
	bool InitProjectsTable();
	bool InitTasksTable();
	bool InitRemindersTable();
	bool InitPasswordsTable();
	bool InitUserPreferencesTable();
	std::string m_db_path;
	mw::DatabaseHandler m_db_handler;
	bool is_initialized;
	std::mutex m_mutex;
};

