#pragma once
#include "model/sqlite3.h"

namespace mw
{
	class SqlStatement
	{
	public:
		SqlStatement();
		sqlite3_stmt* GetStatement();

	private:
		sqlite3_stmt* m_statement;
	};
}


