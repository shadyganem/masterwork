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
	is_initialized = true;
	return true;
}

bool Model::AddUser(mw::User& user)
{
	try
	{
		if (this->ConnectDb() == false)
			return false;
		std::string sql = "INSERT INTO users(username, is_active, status)"
			"VALUES (\"" + user.username + "\" ,"
			+ std::to_string(user.is_active) + " , "
			+ std::to_string(user.status) + 
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

bool Model::AddProject(mwProject& project)
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

		std::string sql = "INSERT INTO tasks(name, parent_uid, description, status, priority, start_time, deadline, project_uid, last_update)"
			"VALUES (\"" + task.name + "\"  ,"
			+ std::to_string(task.parent_uid) + ","
			"\"" + task.description + "\"  ,"
			+ std::to_string(task.status) + ","
			+ std::to_string(task.priority) + ","
			+ std::to_string(task.start_time) + ","
			+ std::to_string(task.deadline) + ","
			+ std::to_string(task.project_uid) + ", "
			+ std::to_string(task.last_update) + " "
			"); ";
		m_db_handler.ExeQuery(sql.c_str());

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
		mw::Logger logger;
		logger.SetLogLevel(mw::LogLevel::DEBUG);
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
		logger.SetLogLevel(mw::LogLevel::DISABLE);

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

		std::string sql = "UPDATE tasks "
			"SET status= " + std::to_string(mw::Task::TaskStatus::DELETED) + " "
			"WHERE uid=" + std::to_string(task.uid) + " "
			";";
		m_db_handler.Update(sql.c_str());

		m_db_handler.Update(sql.c_str());
		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::DeleteProject(mwProject& project)
{
	try
	{
		mw::Logger logger;
		logger.Info("Delete Project" );
		this->ConnectDb();

		std::string sql = "UPDATE projects "
			"SET status= " + std::to_string(mwProject::ProjectStatus::DELETED) + ", "
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

bool Model::GetActiveProject(mwProject& project, mw::User& user)
{
	try
	{
		mw::Logger logger;
		logger.Info("Select active project");
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		std::string sql = "SELECT * FROM projects "
			              "WHERE is_active=1 "
			              "AND user_uid=" + std::to_string(user.uid) +
			              ";";
		Records records;
		logger.Info("Executinig query " + sql);

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

bool Model::GetAllProjects(std::vector<mwProject>& projects_vect, const mw::User& user)
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
		mwProject proj;
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
	catch(...)
	{
		logger.Error("Exception occured at mwModel::GetAllProjects(std::vector<mwProject>& prjects_vect, const mwUser& user) ");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::SetActiveProject(mwProject& project)
{
	mw::Logger logger;
	try
	{
		logger.Info("Update active project");
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

bool Model::GetProjectTasks(mwProject& project, std::vector<mw::Task>& ret_tasks_vect)
{
	std::vector<std::vector<std::string>> records;
	std::string sql = "SELECT * FROM ";
	m_db_handler.Select(sql.c_str(), records);
	return false;
}

bool Model::GetAllTasks(std::vector<mw::Task>& tasks, mwProject& project)
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
						  "AND status!=-1"
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

bool Model::GetArchiveAllTasks(std::vector<mw::Task>& tasks, mwProject& project)
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
			"AND status=-1"
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

bool Model::IsProjectFound(mwProject& project)
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

bool Model::UpdateTask(mw::Task& task)
{
	mw::Logger logger;
	try
	{
		task.StampLastUpdateTime();
		if (task.project_uid == 0)
		{
			throw("Can not add task with project_uid= 0");
		}
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		std::string sql = "UPDATE tasks "
						  "SET name=\"" + task.name + "\", "
						  "description=\"" + task.description + "\", "
						  "status=" + std::to_string(task.status) + ", "
						  "priority=" + std::to_string(task.priority) + ", "
						  "deadline=" + std::to_string(task.deadline) + ", "
						  "last_update=" + std::to_string(task.last_update) + " "
						  "WHERE uid=" + std::to_string(task.uid) + ";";

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

bool Model::UpdateProject(mwProject& project)
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

bool Model::ConnectDb()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;
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
					"PRIMARY KEY(\"uid\" AUTOINCREMENT) "
					"); "

					"INSERT OR IGNORE INTO \"users\" ( "
		            "\"uid\", "
					"\"username\", "
					"\"is_active\", "
                    "\"status\" ) "
					"VALUES ( "
		            "\"1\", "
					"\"Default User\", "
					"\"1\", "
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

	const char* sql =  "CREATE TABLE IF NOT EXISTS \"tasks\" ( "
					   "\"uid\"	INTEGER NOT NULL UNIQUE,       "
                	   "\"parent_uid\"	INTEGER DEFAULT 0,     "
					   "\"name\"	    TEXT,                  "
					   "\"description\"	TEXT,                  "
                	   "\"status\"	    INTEGER DEFAULT 0,     "
                	   "\"priority\"	INTEGER DEFAULT 2,     "
					   "\"start_time\"	INTEGER NOT NULL,      "
					   "\"end_time\"	INTEGER DEFAULT 0,     "
		               "\"deadline\"	INTEGER DEFAULT 0,     "
		               "\"last_update\"	INTEGER DEFAULT 0,     "
					   "\"project_uid\"	INTEGER DEFAULT 1,     "
                	   "\"red\"	        INTEGER DEFAULT 0,     "
		               "\"green\"	    INTEGER DEFAULT 0,     "
		               "\"blue\"	    INTEGER DEFAULT 0,     "
					   "PRIMARY KEY(\"uid\" AUTOINCREMENT)     "
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
	mw::Logger logger;
	logger.Info("Initialzing notifications table");
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"notifications\" ( "
						"\"uid\"	INTEGER NOT NULL UNIQUE,       "
						"\"user_id\"	INTEGER DEFAULT 0,     "
						"\"text\"	    TEXT,                  "
						"\"status\"	    INTEGER DEFAULT 0,     "
						"\"priority\"	INTEGER DEFAULT 2,     "
						"\"start_time\"	INTEGER,               "
						"\"end_time\"	INTEGER,               "
						"\"ttl\"	INTEGER,               "
						"\"red\"	        INTEGER DEFAULT 0,     "
						"\"green\"	    INTEGER DEFAULT 0,     "
						"\"blue\"	    INTEGER DEFAULT 0,     "
						"PRIMARY KEY(\"uid\" AUTOINCREMENT)     "
						")";
	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}