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

	std::string sql = "INSERT INTO tasks(taskname, task_dec, project_uid, creation_time)"
		              "VALUES (\"" + task.task_name + "\","
		              "\"" + task.task_description + "\", "
		              + std::to_string(task.project_id) +  ","
		              + std::to_string(task.task_creation_time) +
		              "); ";
	m_db_handler.ExeQuery(sql.c_str());

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool mwModel::InitUsersTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"users\" ( "
				      "\"uid\"	INTEGER NOT NULL UNIQUE, "
				      "\"username\"	TEXT NOT NULL, "
				      "PRIMARY KEY(\"uid\" AUTOINCREMENT) "
				      ")";

	m_db_handler.ExeQuery(sql);

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool mwModel::InitProjectsTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"projects\" ( "
				      "\"uid\"	INTEGER UNIQUE, "
		              "\"user_uid\"	INTEGER, "
				      "\"project_name\"	TEXT, "
				      "\"project_creation_time\"	INTEGER, "
				      "\"PRIMARY KEY(\"uid\" AUTOINCREMENT) "
				      ")";

	m_db_handler.ExeQuery(sql);

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool mwModel::InitTasksTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;


	const char* sql =  "CREATE TABLE IF NOT EXISTS \"tasks\" ( "
					   "\"UID\"	INTEGER NOT NULL UNIQUE, "
					   "\"taskname\"	TEXT, "
					   "\"task_dec\"	TEXT, "
					   "\"creation_time\"	INTEGER, "
					   "\"project_uid\"	INTEGER, "
					   "PRIMARY KEY(\"UID\" AUTOINCREMENT)"
					   ")";

	m_db_handler.ExeQuery(sql);

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}
