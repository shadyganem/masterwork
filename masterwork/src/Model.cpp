#include "model/Model.h"

Model::Model()
{
	m_db_path = "mw.db";
	is_initialized = false;
}

void Model::SetDbPath(std::string path)
{
	m_db_path = path;
}

bool Model::InitModel()
{
	if (is_initialized)
		return true;

	m_db_handler.CreateDB(this->m_db_path.c_str());
	InitUsersTable();
	InitProjectsTable();
	InitTasksTable();
	InitNotificationsTable();
	InitRemindersTable();
	InitPasswordsTable();
	InitAlertTimesTable();
	is_initialized = true;
	return true;
}

bool Model::AddUser(mw::User& user)
{
	try
	{
		if (this->ConnectDb() == false)
			return false;
		
		std::string sql = "INSERT INTO users(username, is_active, status, hashed_password, is_password_protected)"
			"VALUES (\"" + user.username + "\" ,"
			+ std::to_string(user.is_active) + ", "
			+ std::to_string(user.status) + ", "
			+ " \"" + user.hashed_password + "\" ,"
			+ std::to_string(user.is_password_protected) +
			" ); ";

		m_db_handler.ExeQuery(sql.c_str());

		sql = "SELECT MAX(uid) AS max_uid from users;";
		Records records;

		m_db_handler.Select(sql.c_str(), records);
		if (records.empty())
		{
			m_db_handler.DisConn(this->m_db_path.c_str());
			return false;
		}
		Record row = records[0];
		user.uid = std::stoi(row[0]);
		if (this->DisconnectDb() == false)
			return false;
		return true;
	}
	catch (...)
	{
		mw::Logger logger;
		logger.Debug("Exception while adding user");
		this->DisconnectDb();
		return false;
	}
}

bool Model::AddProject(mw::Project& project)
{
	try
	{
		if (this->ConnectDb() == false)
			return false;
		std::string sql = "INSERT INTO projects(user_uid, name, start_time, is_active) "
			"VALUES (\"" + std::to_string(project.user_uid) + "\"  ,"
			"\"" + project.name + "\" ,"
			+ std::to_string(project.start_time) + ", "
			+ std::to_string(project.is_active) +
			");";

		m_db_handler.ExeQuery(sql.c_str());

		sql = "SELECT MAX(uid) AS max_uid from projects;";
		Records records;

		m_db_handler.Select(sql.c_str(), records);
		if (records.empty())
		{
			m_db_handler.DisConn(this->m_db_path.c_str());
			return false;
		}
		Record row = records[0];
		project.uid = std::stoi(row[0]);

		if (this->DisconnectDb() == false)
			return false;
		return true;
	}
	catch (...)
	{
		mw::Logger logger;
		logger.Debug("Exception while adding project");
		this->DisconnectDb();
		return false;
	}

}

bool Model::AddTask(mw::Task& task)
{
	mw::Logger logger;
	try
	{
		task.StampLastUpdateTime();
		if (task.project_uid == 0)
		{
			throw("Can not add task with UID = 0");
		}
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		int noti_en; 
		noti_en = (task.notification_enabled == true) ? 1 : 0;
		std::string sql = "INSERT INTO tasks(name, parent_uid, description, status, priority, start_time, deadline, project_uid, last_update, notification_enabled)"
			"VALUES (\"" + task.name + "\"  ,"
			+ std::to_string(task.parent_uid) + ","
			"\"" + task.description + "\"  ,"
			+ std::to_string(task.status) + ","
			+ std::to_string(task.priority) + ","
			+ std::to_string(task.creation_time) + ","
			+ std::to_string(task.deadline) + ","
			+ std::to_string(task.project_uid) + ", "
			+ std::to_string(task.last_update) + ", "
			+ std::to_string(noti_en) + " "
			"); ";
		m_db_handler.ExeQuery(sql.c_str());

		sql.clear();
		sql = "SELECT MAX(uid) FROM tasks;";

		Records records;

		m_db_handler.Select(sql.c_str(), records);
		if (records.empty())
		{
			m_db_handler.DisConn(this->m_db_path.c_str());
			return false;
		}
		Record row = records[0];
		task.uid = std::stoi(row[0]);


		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;

	}
	catch (...)
	{
		logger.Error("Exception occured at bool mwModel::AddTask(mwTask& task)");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::AddNotification(mw::Notification& notification)
{
	mw::Logger logger;
	try
	{
		notification.StampLastUpdateTime();
		notification.Hash();
		if (notification.user_uid == 0)
		{
			throw("Can not add Notification with user UID = 0");
		}
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		Records records;


		std::string sql = "SELECT * FROM notifications WHERE hash=" + std::to_string(notification.hash) + " ;";

		m_db_handler.Select(sql.c_str(), records);


		if (records.size() > 0)
		{
			return true;
		}

		sql = "INSERT INTO notifications(user_uid,hash, text, details, status, priority, repeat, start_time, end_time, last_update, ttl, color) "
			              "VALUES (\"" + std::to_string(notification.user_uid) + "\" , "
			              + std::to_string(notification.hash) + ", "
			              "\"" + notification.text + "\","
                          "\"" + notification.details + "\","
			              + std::to_string(notification.status)      + ", "
			              + std::to_string(notification.priority)    + ", "
			              + std::to_string(notification.repeat)      +   ", "
			              + std::to_string(notification.start_time)  + ", "
			              + std::to_string(notification.end_time)    + ", "
			              + std::to_string(notification.last_update) + ", "
			              + std::to_string(notification.ttl)         + ", "
			              + std::to_string(notification.color)       + " "
			              "); ";
		m_db_handler.ExeQuery(sql.c_str());


		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;

	}
	catch (...)
	{
		logger.Error("Exception occured at bool mw::Model::AddNotification(mw::Notification& notification)");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::AddReminder(mw::Reminder& reminder)
{
	mw::Logger logger;
	try
	{
		reminder.StampLastUpdateTime();
		reminder.Hash();
		if (reminder.user_uid == 0)
		{
			throw("Can not add Reminder with user UID = 0");
		}
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		Records records;

		std::string sql = "INSERT INTO reminders(user_uid, hash, title, text, status, priority, repeat,creation_time, reminder_time, end_time, last_update, color) "
			"VALUES (" + std::to_string(reminder.user_uid) + ", "
			+ std::to_string(reminder.hash) + ","
			"\"" + reminder.title + "\","
			"\"" + reminder.text + "\","
			+ std::to_string(reminder.status) + ","
			+ std::to_string(reminder.priority) + ","
			+ std::to_string(reminder.repeat) + ","
			+ std::to_string(reminder.creation_time) + ","
			+ std::to_string(reminder.reminder_time) + ","
			+ std::to_string(reminder.end_time) + ","
		    + std::to_string(reminder.last_update) + ","
			"\"" + reminder.color + "\""
			"); ";

		m_db_handler.ExeQuery(sql.c_str());

		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		{
			return false;
		}
		return true;
	}
	catch (...)
	{
		logger.Error("Exception occured at bool Model::AddReminder(mw::Reminder& reminder)");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::AddPassword(mw::Password& password)
{
	mw::Logger logger;
	try
	{
		password.StampLastUpdateTime();

		if (password.user_uid == 0)
		{
			throw("Can not add Reminder with user UID = 0");
		}
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		Records records;

		std::string sql = "INSERT INTO passwords(user_uid, username, encrypted_password, url, notes, creation_time, last_update, color) "
			"VALUES (" + std::to_string(password.user_uid) + ", "
			"\"" + password.username + "\", "
			"\"" + password.password + "\", "
			"\"" + password.url + "\", "
			"\"" + password.notes + "\", "
			+ std::to_string(password.creation_time) + ", "
			+ std::to_string(password.last_update) + ", "
			+ std::to_string(password.color) + " "
			"); ";
		m_db_handler.ExeQuery(sql.c_str());

		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;

	}
	catch (...)
	{
		logger.Error("Exception occured at bool mw::Model::AddNotification(mw::Notification& notification)");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetActiveUser(mw::User& user)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		std::string sql = "SELECT * FROM users "
			              "WHERE is_active=1 "
			              "; ";
		Records records;

		m_db_handler.Select(sql.c_str(), records);
		if (records.empty())
		{
			m_db_handler.DisConn(this->m_db_path.c_str());
			return false;
		}
		Record row = records[0];
		user.uid = std::stoi(row[0]);
		user.username = row[1];
		user.is_active = std::stoi(row[2]) == 1 ? true : false;
		user.status = std::stoi(row[3]);
		user.hashed_password = row[4];
		user.is_password_protected = (bool)std::stoi(row[5]);
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		mw::Logger logger;
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::SetActiveUser(mw::User& user)
{
	try
	{
		this->ConnectDb();

		std::string sql = "UPDATE users "
					      "SET is_active=0 "
						  "WHERE is_active=1 "
						  ";";

		m_db_handler.Update(sql.c_str());

		sql = "UPDATE users "
			  "SET is_active=1 "
			  "WHERE uid=" + std::to_string(user.uid) +
			  ";";

		m_db_handler.Update(sql.c_str());
		this->DisconnectDb();

	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::DeleteTask(mw::Task& task)
{
	try
	{
		task.StampLastUpdateTime();
		this->ConnectDb();

		std::string sql = "DELETE FROM tasks WHERE uid=" + std::to_string(task.uid) + " ;";

		m_db_handler.ExeQuery(sql.c_str());

		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::DeleteReminder(mw::Reminder& reminder)
{
	try
	{
		reminder.StampLastUpdateTime();
		this->ConnectDb();

		std::string sql = "DELETE FROM reminders WHERE uid=" + std::to_string(reminder.uid) + " ;";

		m_db_handler.ExeQuery(sql.c_str());

		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}

}

bool Model::ArchiveTask(mw::Task& task)
{
	try
	{
		task.StampLastUpdateTime();
		this->ConnectDb();

		std::string sql = "UPDATE tasks "
			"SET archived= 1 "
			"WHERE uid=" + std::to_string(task.uid) + " ;";
			

		m_db_handler.Update(sql.c_str());

		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::UnarchiveTask(mw::Task& task)
{
	try
	{
		task.StampLastUpdateTime();
		this->ConnectDb();

		std::string sql = "UPDATE tasks "
			"SET archived= 0 "
			"WHERE uid=" + std::to_string(task.uid) + " ;";


		m_db_handler.Update(sql.c_str());

		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::DeleteProject(mw::Project& project)
{
	try
	{
		mw::Logger logger;
		logger.Info("Delete Project" );
		this->ConnectDb();

		std::string sql = "UPDATE projects "
			"SET status= " + std::to_string(mw::Project::ProjectStatus::DELETED) + ", "
			"is_active=0 " 
			"WHERE uid=" + std::to_string(project.uid) + " "
			";";
		m_db_handler.Update(sql.c_str());

		logger.Info(sql);

		m_db_handler.Update(sql.c_str());
		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::GetAllUsers(std::vector<mw::User>& ret_users_vect)
{
	try
	{
		this->ConnectDb();
		mw::Logger logger;
		Records records;
		Record row;
		mw::User user;
		std::string sql = "SELECT * FROM users;";
		m_db_handler.Select(sql.c_str(), records);
		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}
		for (int i = 0; i < records.size(); i++)
		{
			row = records[i];
			user.uid = std::stoi(row[0]);
			user.username = row[1];
			user.is_active = std::stoi(row[2]) == 1 ? true : false;
			user.status = std::stoi(row[3]);
			user.hashed_password = row[4];
			user.is_password_protected = (bool)std::stoi(row[5]);
			ret_users_vect.push_back(user);
		}
		this->DisconnectDb();
		return true;
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::GetActiveProject(mw::Project& project, mw::User& user)
{
	try
	{
		mw::Logger logger;
		
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		std::string sql = "SELECT * FROM projects "
			              "WHERE is_active=1 "
			              "AND user_uid=" + std::to_string(user.uid) +
			              ";";
		Records records;

		m_db_handler.Select(sql.c_str(), records);
		if (records.empty())
		{
			project.uid = 0;
			logger.Warning("No records were found for: " + sql);
			m_db_handler.DisConn(this->m_db_path.c_str());
			return false;
		}
		Record row = records[0];

		project.uid = std::stoi(row[0]);
		project.user_uid = std::stoi(row[1]);
		project.name = row[2];
		project.start_time = std::stoi(row[3]);
		project.is_active = std::stoi(row[4]) == 1 ? true : false;
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetAllProjects(std::vector<mw::Project>& projects_vect, const mw::User& user)
{
	mw::Logger logger;
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		logger.Info("selecting all projects for " + user.username);
		Records records;
		Record row;
		std::string sql = "SELECT * FROM projects WHERE user_uid=" + std::to_string(user.uid) + " "
			              "AND status!=-1 ;";
		logger.Info("Executinig query " + sql);
		m_db_handler.Select(sql.c_str(), records);
		mw::Project proj;
		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}
		for (int i = 0; i < records.size(); i++)
		{
			row = records[i];
			proj.uid = std::stoi(row[0]);
			proj.user_uid = std::stoi(row[1]);
			proj.name = row[2];
			proj.start_time = std::stoi(row[3]);
			proj.status = std::stoi(row[4]);
			proj.is_active = std::stoi(row[5]) == 1 ? true : false;
			projects_vect.push_back(proj);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch(const std::exception& e)
	{
		logger.Error("The exception is: " + std::string(e.what()));
		logger.Error("Exception occured at mwModel::GetAllProjects(std::vector<mwProject>& prjects_vect, const mwUser& user) ");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetAllNotifications(std::vector<mw::Notification>& notifications_vect, const mw::User& currnet_user)
{
	mw::Logger logger;
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		Records records;
		Record row;


		std::string sql = "SELECT * FROM notifications WHERE user_uid=" + std::to_string(currnet_user.uid) + " "
			"AND repeat>0 ;";


		m_db_handler.Select(sql.c_str(), records);

		mw::Notification notification;

		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}

		for (int i = 0; i < records.size(); i++)
		{
			row = records[i];
			notification.uid = std::stoi(row[0]);
			notification.user_uid = std::stoi(row[1]);
			notification.hash = std::stoull(row[2]);
			notification.text = row[3];
			notification.details = row[4];
			notification.status = (mw::NotificationStatus)std::stoi(row[5]);
			notification.priority = std::stoi(row[6]);
			notification.repeat = std::stoi(row[7]);
			notification.start_time = std::stoi(row[8]);
			notification.end_time = std::stoi(row[9]);
			notification.last_update = std::stoi(row[10]);
			notification.ttl = std::stoi(row[11]);
			notification.color = std::stoi(row[12]);

			notifications_vect.push_back(notification);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		logger.Error("Exception occured at mwModel::GetAllProjects(std::vector<mwProject>& prjects_vect, const mwUser& user) ");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetAllReminders(std::vector<mw::Reminder>& reminders, const mw::User& current_user)
{
	mw::Logger logger;
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		Records records;
		Record row;


		std::string sql = "SELECT * FROM reminders WHERE user_uid=" + std::to_string(current_user.uid) + " ;";


		m_db_handler.Select(sql.c_str(), records);


		mw::Reminder reminder;

		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}

		for (int i = 0; i < records.size(); i++)
		{

			row = records[i];
			reminder.uid = std::stoi(row[0]);
			reminder.user_uid = std::stoi(row[1]);
			reminder.hash = std::stoull(row[2]);
			reminder.title = row[3];
			reminder.text = row[4];
			reminder.status = (mw::ReminderStatus)std::stoi(row[5]);
			reminder.priority = std::stoi(row[6]);
			reminder.repeat = std::stoi(row[7]);
			reminder.creation_time = std::stoi(row[8]);
			reminder.reminder_time = std::stoi(row[9]);
			reminder.end_time = std::stoi(row[10]);
			reminder.last_update = std::stoi(row[11]);
			reminder.color = row[12];

			reminders.push_back(reminder);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		logger.Error("Exception occured at Model::GetAllReminders(std::vector<mw::Reminder>& reminders, const mw::User& current_user) ");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetAllPasswords(std::vector<mw::Password>& passwords, const mw::User& current_user)
{
	mw::Logger logger;
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		Records records;
		Record row;


		std::string sql = "SELECT * FROM passwords WHERE user_uid=" + std::to_string(current_user.uid) + " ;";


		m_db_handler.Select(sql.c_str(), records);


		mw::Password password;

		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}

		for (int i = 0; i < records.size(); i++)
		{

			row = records[i];
			password.uid = std::stoi(row[0]);
			password.user_uid = std::stoi(row[1]);
			password.username = row[2];
			password.encrypted_password = row[3];
			password.url = row[4];
			password.notes = row[5];
			password.creation_time = std::stoi(row[6]);
			password.last_update = std::stoi(row[7]);
			password.color = std::stoi(row[8]);

			passwords.push_back(password);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		logger.Error("Exception occured at mwModel::GetAllProjects(std::vector<mwProject>& prjects_vect, const mwUser& user) ");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::SetActiveProject(mw::Project& project)
{
	mw::Logger logger;
	try
	{
		this->ConnectDb();

		std::string sql = "UPDATE projects "
			              "SET is_active=0 "
			              "WHERE is_active=1 "
			              "AND user_uid=" + std::to_string(project.user_uid) +
			              ";";

		m_db_handler.Update(sql.c_str());

		sql = "UPDATE projects "
			  "SET is_active=1 "
			  "WHERE uid=" + std::to_string(project.uid) + " "
			  "AND user_uid= " + std::to_string(project.user_uid) +
			  ";";

		m_db_handler.Update(sql.c_str());
		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::GetAllTasks(std::vector<mw::Task>& tasks, mw::Project& project)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		mw::Logger logger;
		logger.Info("selecting all tasks for " + project.name);
		Records records;
		Record row;
		std::string sql = "SELECT * FROM tasks WHERE project_uid=" + std::to_string(project.uid) + " "
						  "AND archived=0"
			              ";";
		logger.Info("Executinig query " + sql);
		m_db_handler.Select(sql.c_str(), records);
		mw::Task task;
		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}
		for (int i = 0; i < records.size(); i++)
		{
			row = records[i];
			task.uid = std::stoi(row[0]);
			task.parent_uid = std::stoi(row[1]);
			task.name = row[2];
			task.description = row[3];
			task.status = std::stoi(row[4]);
			task.priority = std::stoi(row[5]);
			task.creation_time = std::stoi(row[6]);
			task.end_time = std::stoi(row[7]);
			task.deadline = std::stoi(row[8]);
			task.last_update = std::stoi(row[9]);
			task.project_uid = std::stoi(row[10]);
			task.red = std::stoi(row[11]);
			task.green = std::stoi(row[12]);
			task.blue = std::stoi(row[13]);
			task.notification_enabled = (std::stoi(row[14]) == 1) ? true : false;
			tasks.push_back(task);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetArchiveAllTasks(std::vector<mw::Task>& tasks, mw::Project& project)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		mw::Logger logger;
		Records records;
		Record row;
		std::string sql = "SELECT * FROM tasks WHERE project_uid=" + std::to_string(project.uid) + " "
			"AND archived=1"
			";";		
		m_db_handler.Select(sql.c_str(), records);
		mw::Task task;
		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}
		for (int i = 0; i < records.size(); i++)
		{
			row = records[i];
			task.uid = std::stoi(row[0]);
			task.parent_uid = std::stoi(row[1]);
			task.name = row[2];
			task.description = row[3];
			task.status = std::stoi(row[4]);
			task.priority = std::stoi(row[5]);
			task.start_time = std::stoi(row[6]);
			task.end_time = std::stoi(row[7]);
			task.deadline = std::stoi(row[8]);
			task.last_update = std::stoi(row[9]);
			task.project_uid = std::stoi(row[10]);
			task.red = std::stoi(row[11]);
			task.green = std::stoi(row[12]);
			task.blue = std::stoi(row[13]);
			tasks.push_back(task);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetArchiveAllTasks(std::vector<mw::Task>& tasks, mw::Project& current_project, unsigned int num_of_days)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;
		auto current_epoch_time = std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()
			).count();

		mw::Logger logger;
		logger.Info("selecting all tasks for " + current_project.name);
		Records records;
		Record row;
		std::string sql = "SELECT * FROM tasks WHERE project_uid=" + std::to_string(current_project.uid) + " "
			"AND archived=1" + " "
			"AND last_update >= " + std::to_string(current_epoch_time - num_of_days*24*60*60) + " " 
			";";
		logger.Info("Executinig query " + sql);
		m_db_handler.Select(sql.c_str(), records);
		mw::Task task;
		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}
		for (int i = 0; i < records.size(); i++)
		{
			row = records[i];
			task.uid = std::stoi(row[0]);
			task.parent_uid = std::stoi(row[1]);
			task.name = row[2];
			task.description = row[3];
			task.status = std::stoi(row[4]);
			task.priority = std::stoi(row[5]);
			task.start_time = std::stoi(row[6]);
			task.end_time = std::stoi(row[7]);
			task.deadline = std::stoi(row[8]);
			task.last_update = std::stoi(row[9]);
			task.project_uid = std::stoi(row[10]);
			task.red = std::stoi(row[11]);
			task.green = std::stoi(row[12]);
			task.blue = std::stoi(row[13]);
			tasks.push_back(task);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::IsTaskFound(mw::Task& task)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		mw::Logger logger;
		Records records;
		bool found = true;
		std::string sql = "SELECT * FROM tasks WHERE uid=" + std::to_string(task.uid) + " "
		                  "AND archived=0"
			              ";";

		logger.Info("Executinig query " + sql);
		m_db_handler.Select(sql.c_str(), records);
		mw::Task task;
		if (records.empty())
			found = false;

		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return found;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::IsProjectFound(mw::Project& project)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		mw::Logger logger;
		Records records;
		bool found = true;
		std::string sql = "SELECT * FROM projects WHERE uid=" + std::to_string(project.uid) + " "
			              "AND status!=-1"
			              ";";

		logger.Info("Executinig query " + sql);
		m_db_handler.Select(sql.c_str(), records);
		mw::Task task;
		if (records.empty())
			found = false;

		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return found;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::IsUserFound(mw::User& user)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		mw::Logger logger;
		Records records;
		bool found = true;
		std::string sql = "SELECT * FROM users WHERE uid=" + std::to_string(user.uid) + " ;";

		m_db_handler.Select(sql.c_str(), records);
		mw::Task task;
		if (records.empty())
			found = false;

		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return found;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::UpdateTask(mw::Task& task) {
	mw::Logger logger;

	try {
		task.StampLastUpdateTime();

		if (task.project_uid == 0) {
			throw std::runtime_error("Cannot update task with project_uid=0");
		}

		// Use parameterized query
		std::string sql = "UPDATE tasks "
			"SET name=?, description=?, status=?, priority=?, deadline=?, last_update=?, notification_enabled=? "
			"WHERE uid=?;";

		logger.Info("Executing query: " + sql);

		// RAII for database connection
		if (!m_db_handler.Conn(this->m_db_path.c_str())) {
			logger.Error("Failed to connect to the database.");
			return false;
		}

		sqlite3_stmt* statement;
		m_db_handler.Prepare(sql.c_str(), &statement);

		// Bind parameters
		sqlite3_bind_text(statement, 1, task.name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(statement, 2, task.description.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(statement, 3, task.status);
		sqlite3_bind_int(statement, 4, task.priority);
		sqlite3_bind_int64(statement, 5, task.deadline);
		sqlite3_bind_int64(statement, 6, task.last_update);
		sqlite3_bind_int(statement, 7, task.notification_enabled ? 1 : 0);
		sqlite3_bind_int64(statement, 8, task.uid);

		// Execute the statement
		m_db_handler.Step(statement);
		m_db_handler.Finalize(statement);

		// Commit the transaction (if you are using transactions)
		// m_db_handler.Commit();

		// Disconnect in destructor (RAII)
		return true;
	}
	catch (const std::exception& e) {
		logger.Error("Exception occurred: " + std::string(e.what()));
		return false;
	}
}

bool Model::UpdateProject(mw::Project& project)
{
	mw::Logger logger;
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		std::string sql = "UPDATE projects "
			              "SET name=\"" + project.name + "\" "
			              "WHERE uid=" + std::to_string(project.uid) + " ;";

		logger.Info("Executinig query " + sql);

		m_db_handler.Update(sql.c_str());

		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		logger.Error("Exception occured at bool mwModel::AddTask(mwTask& task)");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::UpdateUser(mw::User& user)
{
	mw::Logger logger;
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		std::string sql = "UPDATE users "
			"SET username=\"" + user.username + "\", "
			"status=\"" + std::to_string(user.status) + "\" "
			"hashed_password=\"" + user.hashed_password + "\" "
			"WHERE uid=" + std::to_string(user.uid) + " ;";

		logger.Info("Executinig query " + sql);

		m_db_handler.Update(sql.c_str());

		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		logger.Error("Exception occured at bool mwModel::AddTask(mwTask& task)");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::UpdateNotification(mw::Notification& notification)
{
	try
	{
		notification.StampLastUpdateTime();

		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		std::string sql = "UPDATE notifications "
			"SET text=\"" + notification.text + "\", "
			"details=\"" + notification.details +"\", "
			"status=\"" + std::to_string(notification.status) + "\", "
			"priority=\"" + std::to_string(notification.priority) + "\", "
			"repeat=\"" + std::to_string(notification.repeat) + "\", "
			"end_time=\"" + std::to_string(notification.end_time) + "\", "
			"last_update=\"" + std::to_string(notification.last_update) + "\", "
			"ttl=\"" + std::to_string(notification.ttl) + "\", "
			"color=\"" + std::to_string(notification.color) + "\" "

			"WHERE uid=" + std::to_string(notification.uid) + " ;";

		m_db_handler.Update(sql.c_str());

		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		mw::Logger logger;
		logger.Error("Exception occured at bool mwModel::AddTask(mwTask& task)");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::ConnectDb()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		throw "Failed to connect to DB ";
	return true;
}

bool Model::DisconnectDb()
{
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitUsersTable()
{
	mw::Logger logger;
	logger.Info("Initialzing users table");
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"users\" ( "
					"\"uid\"	INTEGER NOT NULL UNIQUE, "
					"\"username\"	TEXT NOT NULL, "
					"\"is_active\"  NUMERIC NOT NULL DEFAULT 0, "
             		"\"status\"     NUMERIC NOT NULL DEFAULT 0, "
					"\"hashed_password\" TEXT NOT NULL, "
					"\"is_password_protected\" NUMERIC NOT NULL DEFAULT 0, "
					"PRIMARY KEY(\"uid\" AUTOINCREMENT) "
					"); "

					"INSERT OR IGNORE INTO \"users\" ( "
		            "\"uid\", "
					"\"username\", "
					"\"is_active\", "
                    "\"status\" , "
					"\"hashed_password\" , "
					"\"is_password_protected\")"
					"VALUES ( "
		            "\"1\", "
					"\"Default User\", "
					"\"1\", "
		            "\"0\" , "
					"\"$2a$12$U8YKViISROZEWkabHvseXujY64NhQxpvklgek20SDClb2yP7oK.kW\" , "
		            "\"0\" ); ";

	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitProjectsTable()
{
	mw::Logger logger;
	logger.Info("Initialzing projects table");
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"projects\" (    "
				      "\"uid\"	        INTEGER NOT NULL UNIQUE,    "
		              "\"user_uid\"	    INTEGER NOT NULL DEFAULT 1, "
				      "\"name\"	        TEXT,                       "
				      "\"start_time\"   INTEGER,                    "
                	  "\"status\"       INTEGER NOT NULL DEFAULT 0, "
                      "\"is_active\"	NUMERIC NOT NULL DEFAULT 0, "
                      "PRIMARY KEY(\"uid\" AUTOINCREMENT)           "
				      ")";
	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitTasksTable()
{
	mw::Logger logger;
	logger.Info("Initialzing tasks table");
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql =  "CREATE TABLE IF NOT EXISTS \"tasks\" (      "
					   "\"uid\"	INTEGER NOT NULL UNIQUE,            "
                	   "\"parent_uid\"	INTEGER DEFAULT 0,          "
					   "\"name\"	    TEXT,                       "
					   "\"description\"	TEXT,                       "
                	   "\"status\"	    INTEGER DEFAULT 0,          "
                	   "\"priority\"	INTEGER DEFAULT 2,          "
					   "\"start_time\"	INTEGER NOT NULL,           "
					   "\"end_time\"	INTEGER DEFAULT 0,          "
		               "\"deadline\"	INTEGER DEFAULT 0,          "
		               "\"last_update\"	INTEGER DEFAULT 0,          "
					   "\"project_uid\"	INTEGER DEFAULT 1,          "
                	   "\"red\"	        INTEGER DEFAULT 0,          "
		               "\"green\"	    INTEGER DEFAULT 0,          "
		               "\"blue\"	    INTEGER DEFAULT 0,          "
					   "\"notification_enabled\" BOLLEAN DEFAULT 1, "
					   "\"archived\"	INTEGER DEFAULT 0,          "
					   "PRIMARY KEY(\"uid\" AUTOINCREMENT)          "
					   ")";
	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitNotificationsTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"notifications\" (      "
						"\"uid\"	        INTEGER NOT NULL UNIQUE,       "
						"\"user_uid\"	    INTEGER NOT NULL DEFAULT 1,    "
						"\"hash\"	        BIGINT NOT NULL DEFAULT 0,    "
						"\"text\"	        TEXT,                          "
		                "\"details\"	    TEXT NOT NULL ,    "
						"\"status\"	        INTEGER NOT NULL DEFAULT 0,    "
						"\"priority\"	    INTEGER NOT NULL DEFAULT 2,    "
		                "\"repeat\"	        INTEGER NOT NULL DEFAULT 1,    "
						"\"start_time\"	    INTEGER NOT NULL,              "
						"\"end_time\"	    INTEGER NOT NULL DEFAULT 0,    "
                 		"\"last_update\"	INTEGER NOT NULL DEFAULT 0,    "
						"\"ttl\"	        INTEGER NOT NULL DEFAULT 0,    "
						"\"color\"	        INTEGER DEFAULT -1,            "
						"PRIMARY KEY(\"uid\" AUTOINCREMENT)                "
						")";
	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitRemindersTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"reminders\" (      "
		"\"uid\"	         INTEGER NOT NULL UNIQUE,       "
		"\"user_uid\"	     INTEGER NOT NULL DEFAULT 1,    "
		"\"hash\"	         BIGINT NOT NULL DEFAULT 0,     "
		"\"title\"	         TEXT NOT NULL ,                "
		"\"text\"	         TEXT,                          "
		"\"status\"	         INTEGER NOT NULL DEFAULT 0,    "
		"\"priority\"	     INTEGER NOT NULL DEFAULT 2,    "
		"\"repeat\"	         INTEGER NOT NULL DEFAULT 1,    "
		"\"creation_time\"	 INTEGER NOT NULL,              "
		"\"reminder_time\"	 INTEGER NOT NULL,              "
		"\"end_time\"	     INTEGER NOT NULL DEFAULT 0,    "
		"\"last_update\"	 INTEGER NOT NULL DEFAULT 0,    "
		"\"color\"	         TEXT DEFAULT '#FFFFFF',        "
		"PRIMARY KEY(\"uid\" AUTOINCREMENT)                 "
		")";
	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitPasswordsTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"passwords\" (      "
		"\"uid\"	            INTEGER NOT NULL UNIQUE,    "
		"\"user_uid\"	        INTEGER NOT NULL DEFAULT 1, "
		"\"username\"	        TEXT NOT NULL,              "
		"\"encrypted_password\" TEXT NOT NULL ,             "
		"\"url\"	            TEXT,                       "
		"\"notes\"	            TEXT,                       "
		"\"creation_time\"	 INTEGER NOT NULL,              "
		"\"last_update\"	 INTEGER NOT NULL DEFAULT 0,    "
		"\"color\"	         INTEGER DEFAULT -1,            "
		"PRIMARY KEY(\"uid\" AUTOINCREMENT)                 "
		")";
	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitAlertTimesTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"reminder_alert_times\" (      "
		"\"uid\"	INTEGER NOT NULL UNIQUE,"
		"\"reminder_uid\"	    INTEGER NOT NULL,"
		"\"value\"              INTEGER NOT NULL,"
		"PRIMARY KEY(\"uid\" AUTOINCREMENT)"
		");";

	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}
