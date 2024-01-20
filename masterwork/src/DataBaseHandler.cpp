#include "model/DataBaseHandler.h"

mw::DataBaseHandler::DataBaseHandler()
{
	m_db = NULL;
	is_conn = false;
}

int mw::DataBaseHandler::Sqlite3SelectCallback(void* p_data, int num_fields, char** p_fields, char** p_col_names)
{
	mw::Logger logger;
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

int mw::DataBaseHandler::Sqlite3UpdateCallback(void* p_data, int num_fields, char** p_fields, char** p_col_names)
{
	mw::Logger logger;
	logger.Info("callback is called");
	return 0;
}

bool mw::DataBaseHandler::CreateDB(const char* path)
{
	sqlite3* db;
	int rc = sqlite3_open(path, &db);
	if (rc)
		return false;
	sqlite3_close(db);
	return true;
}

bool mw::DataBaseHandler::ExeQuery(const char* sql)
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

bool mw::DataBaseHandler::Select(const char* sql, Records& ret_records)
{
	char* errmsg;
	int rc = sqlite3_exec(m_db, sql, Sqlite3SelectCallback, &ret_records, &errmsg);
	if (rc != SQLITE_OK) 
	{
		return false;
	}
	return true;
}

bool mw::DataBaseHandler::Update(const char* sql)
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

bool mw::DataBaseHandler::CreateNewTable(const char* sql)
{
	return false;
}

bool mw::DataBaseHandler::Conn(const char* path)
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

bool mw::DataBaseHandler::DisConn(const char* path)
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

bool mw::DataBaseHandler::Prepare(const char* sql, sqlite3_stmt** statement)
{
	int result = sqlite3_prepare_v2(m_db, sql, -1, statement, nullptr);
	return (result == SQLITE_OK);
}

bool mw::DataBaseHandler::Step(sqlite3_stmt* statement)
{
	int result = sqlite3_step(statement);
	return (result == SQLITE_DONE || result == SQLITE_ROW);
}

bool mw::DataBaseHandler::Finalize(sqlite3_stmt* statement)
{
	int result = sqlite3_finalize(statement);
	return (result == SQLITE_OK);
}
