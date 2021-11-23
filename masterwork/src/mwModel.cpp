#include "model/mwModel.h"

mwModel::mwModel()
{
	m_db_path = "mw.db";
	is_initialized = false;
}

void mwModel::SetDbPath(std::string path)
{
	m_db_path = path;
}

bool mwModel::InitModel()
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

bool mwModel::AddUser(mwUser& user)
{
	return false;
}

bool mwModel::AddProject(mwProject& project)
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	std::string sql = "";
	m_db_handler.ExeQuery(sql.c_str());

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool mwModel::AddTask(mwTask& task)
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	std::string sql = "INSERT INTO tasks(name, parent_uid, description, status, priority, start_time, deadline, project_uid)"
		              "VALUES (\"" + task.name          + "\"  ,"
		              + std::to_string(task.parent_uid) +     ","
		              "\"" + task.description           + "\"  ,"
                      + std::to_string(task.status)     +     ","
                	  + std::to_string(task.priority)   +	  ","
		              + std::to_string(task.start_time) +     ","
                	  + std::to_string(task.deadline)   +     ","
                	  +std::to_string(task.project_uid) +
		              "); ";
	m_db_handler.ExeQuery(sql.c_str());

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool mwModel::GetActiveUser(mwUser& user)
{
	return false;
}

bool mwModel::SetActiveUser(mwUser& user)
{
	return false;
}

bool mwModel::GetAllUsers(std::vector<mwUser>& ret_users_vect)
{
	return false;
}

bool mwModel::GetActiveProject(mwProject& project)
{
	return false;
}

bool mwModel::SetActiveProject(mwProject& project)
{
	return false;
}

bool mwModel::GetProjectTasks(mwProject& project, std::vector<mwTask>& ret_tasks_vect)
{
	std::vector<std::vector<std::string>> records;
	std::string sql = "SELECT * FROM ";
	m_db_handler.Select(sql.c_str(), records);
	return false;
}

bool mwModel::InitUsersTable()
{
	mwLogger logger;
	logger.Info("Initialzing users table");
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"users\" ( "
				      "\"uid\"	INTEGER NOT NULL UNIQUE, "
				      "\"username\"	TEXT NOT NULL, "
                      "\"is_active\" NUMERIC NOT NULL DEFAULT 0, "
				      "PRIMARY KEY(\"uid\" AUTOINCREMENT) "
				      ")";
	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool mwModel::InitProjectsTable()
{
	mwLogger logger;
	logger.Info("Initialzing projects table");
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"projects\" (    "
				      "\"uid\"	        INTEGER NOT NULL UNIQUE,    "
		              "\"user_uid\"	    INTEGER,                    "
				      "\"name\"	        TEXT,                       "
				      "\"start_time\"   INTEGER,                    "
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

bool mwModel::InitTasksTable()
{
	mwLogger logger;
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
					   "\"start_time\"	INTEGER,               "
					   "\"end_time\"	INTEGER,               "
		               "\"deadline\"	INTEGER,               "
					   "\"project_uid\"	INTEGER DEFAULT 0,     "
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

bool mwModel::InitNotificationsTable()
{
	mwLogger logger;
	logger.Info("Initialzing users table");
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
