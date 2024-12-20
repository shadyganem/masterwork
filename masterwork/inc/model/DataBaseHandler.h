#pragma once
#include "model/sqlite3.h"
#include <string>
#include <vector>
#include "controller/Logger.h"
#include <utility>
#include "model/SqlStatement.h"
#include <string>

using Record = std::vector<std::string>;
using Records = std::vector<std::vector<std::string>>;

namespace mw
{
	class DatabaseHandler
	{
	public:
		DatabaseHandler();
		static int Sqlite3SelectCallback(void* pdata, int argc, char** argv, char** azColName);
		static int Sqlite3UpdateCallback(void* pdata, int argc, char** argv, char** azColName);
		bool CreateDB(const char* path);
		bool ExeQuery(const char* sql);
		bool Select(const char* sql, Records& records);
		bool Update(const char* sql);
		bool CreateNewTable(const char* sql);
		bool Conn(const char* path);
		bool DisConn(const char* path);
		bool BindText(mw::SqlStatement statement, std::string text);

		virtual bool Prepare(const char* sql, sqlite3_stmt** statement);
		virtual bool Step(sqlite3_stmt* statement);
		virtual bool Finalize(sqlite3_stmt* statement);

	private:
		sqlite3* m_db;
		std::string m_path;
		bool is_conn;
		std::vector<std::vector<std::string>> m_records;
	};

}

