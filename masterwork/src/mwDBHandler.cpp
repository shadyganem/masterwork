#include "model/mwDBHandler.h"


static int callback(void* NotUsed, int argc, char** argv, char** azColName) 
{
	return 0;
}

mwDBHandler::mwDBHandler()
{
	m_db = NULL;
	is_conn = false;
}

bool mwDBHandler::CreateDB(const char* path)
{
	sqlite3* db;
	int rc;
	char* zErrMsg = 0;
	rc = sqlite3_open(path, &db);
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
	char* zErrMsg = 0;
	rc = sqlite3_exec(m_db, sql, callback, 0, &zErrMsg);
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
