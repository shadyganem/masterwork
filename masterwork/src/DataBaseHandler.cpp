#include "model/DatabaseHandler.h"

mw::DatabaseHandler::DatabaseHandler()
{
	m_db = NULL;
	is_conn = false;
}

int mw::DatabaseHandler::Sqlite3SelectCallback(void* p_data, int num_fields, char** p_fields, char** p_col_names)
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

int mw::DatabaseHandler::Sqlite3UpdateCallback(void* p_data, int num_fields, char** p_fields, char** p_col_names)
{
	mw::Logger logger;
	logger.Info("callback is called");
	return 0;
}

bool mw::DatabaseHandler::CreateDB(const char* path)
{
	sqlite3* db;
	int rc = sqlite3_open(path, &db);
	if (rc)
		return false;
	sqlite3_close(db);
	return true;
}

bool mw::DatabaseHandler::ExeQuery(const char* sql)
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

bool mw::DatabaseHandler::Select(const char* sql, Records& ret_records)
{
	char* errmsg;
	int rc = sqlite3_exec(m_db, sql, Sqlite3SelectCallback, &ret_records, &errmsg);
	if (rc != SQLITE_OK) 
	{
		return false;
	}
	return true;
}

bool mw::DatabaseHandler::Update(const char* sql)
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

bool mw::DatabaseHandler::CreateNewTable(const char* sql)
{
	return false;
}

bool mw::DatabaseHandler::Conn(const char* path)
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

bool mw::DatabaseHandler::DisConn(const char* path)
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

bool mw::DatabaseHandler::BindText(mw::SqlStatement statement, std::string text)
{
	return false;
}

bool mw::DatabaseHandler::Prepare(const char* sql, sqlite3_stmt** statement)
{
	int result = sqlite3_prepare_v2(m_db, sql, -1, statement, nullptr);
	return (result == SQLITE_OK);
}

bool mw::DatabaseHandler::Step(sqlite3_stmt* statement)
{
	int result = sqlite3_step(statement);
	return (result == SQLITE_DONE || result == SQLITE_ROW);
}

bool mw::DatabaseHandler::Finalize(sqlite3_stmt* statement)
{
	int result = sqlite3_finalize(statement);
	return (result == SQLITE_OK);
}
