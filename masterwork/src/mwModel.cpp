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
	return false;
}

bool mwModel::AddTask(mwTask& task)
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE users ( id int, username text); ";
	m_db_handler.ExeQuery(sql);

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool mwModel::InitUsersTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE users ( id int, username text); ";
	m_db_handler.ExeQuery(sql);

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool mwModel::InitProjectsTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE projects ( id int, projectname text );";
	m_db_handler.ExeQuery(sql);

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool mwModel::InitTasksTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE tasks ( id int, projectname text );";
	m_db_handler.ExeQuery(sql);

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}
