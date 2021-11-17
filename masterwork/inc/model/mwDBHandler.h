#pragma once
#include "model/sqlite3.h"
#include <string>
#include <vector>

using Record = std::vector<std::string>;
using Records = std::vector<std::vector<std::string>>;

class mwDBHandler
{
public:
	mwDBHandler();
	static int Sqlite3SelectCallback(void* pdata, int argc, char** argv, char** azColName);
	static int Sqlite3UpdateCallback(void* pdata, int argc, char** argv, char** azColName);
	bool CreateDB(const char* path);
	bool ExeQuery(const char* sql);
	bool Select(const char* sql, Records& records);
	bool CreateNewTable(const char* sql);
	bool Conn(const char* path);
	bool DisConn(const char* path);
private:
	sqlite3* m_db;
	std::string m_path;
	bool is_conn;
	std::vector<std::vector<std::string>> records;
};

