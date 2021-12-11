#include "model/mwDBHandler.h"

mwDBHandler::mwDBHandler()
{
	m_db = NULL;
	is_conn = false;
}

int mwDBHandler::Sqlite3SelectCallback(void* p_data, int num_fields, char** p_fields, char** p_col_names)
{
	Records* records = static_cast<Records*>(p_data);
	try
	{
		records->emplace_back(p_fields, p_fields + num_fields);
	}
	catch (...)
	{
		return 1;
	}
	return 0;
}

int mwDBHandler::Sqlite3UpdateCallback(void* p_data, int num_fields, char** p_fields, char** p_col_names)
{
	mwLogger logger;
	logger.Info("callback is called");
	return 0;
}

bool mwDBHandler::CreateDB(const char* path)
{
	sqlite3* db;
	int rc = sqlite3_open(path, &db);
	if (rc)
		return false;
	sqlite3_close(db);
	return true;
}

bool mwDBHandler::ExeQuery(const char* sql)
{
	if (is_conn == false)
		return false;
	int rc;
	char* errmsg;
	rc = sqlite3_exec(m_db, sql, Sqlite3UpdateCallback, 0, &errmsg);
	if (rc != SQLITE_OK)
	{
		return false;
	}
	return true;
}

bool mwDBHandler::Select(const char* sql, Records& ret_records)
{
	char* errmsg;
	int rc = sqlite3_exec(m_db, sql, Sqlite3SelectCallback, &ret_records, &errmsg);
	if (rc != SQLITE_OK) 
	{
		return false;
	}
	return true;
}

bool mwDBHandler::Update(const char* sql)
{
	if (is_conn == false)
		return false;
	int rc;
	char* errmsg;
	rc = sqlite3_exec(m_db, sql, Sqlite3UpdateCallback, 0, &errmsg);
	if (rc != SQLITE_OK)
	{
		return false;
	}
	return true;
}

bool mwDBHandler::CreateNewTable(const char* sql)
{
	return false;
}

bool mwDBHandler::Conn(const char* path)
{
	if (this->is_conn)
		return true;
	m_path = path;
	int rc;
	rc = sqlite3_open(path, &this->m_db);
	if (rc)
		return false;
	this->is_conn = true;
	return true;
}

bool mwDBHandler::DisConn(const char* path)
{
	if (this->is_conn == false)
		return true;
	int rc;
	rc = sqlite3_close(this->m_db);
	if (rc)
		return false;
	this->is_conn = false;
	return true;
}
