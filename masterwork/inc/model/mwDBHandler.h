#pragma once
#include "model/sqlite3.h"
#include <string>

class mwDBHandler
{
public:
	mwDBHandler();
	bool CreateDB(const char* path);
	bool ExeQuery(const char* sql);
	bool CreateNewTable(const char* sql);
	bool Conn(const char* path);
	bool DisConn(const char* path);
private:
	sqlite3* m_db;
	std::string m_path;
	bool is_conn;
};

