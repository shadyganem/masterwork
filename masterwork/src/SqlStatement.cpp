#include "model/SqlStatement.h"

mw::SqlStatement::SqlStatement()
{
}

sqlite3_stmt* mw::SqlStatement::GetStatement()
{
	return m_statement;
}
