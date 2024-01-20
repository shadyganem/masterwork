#include "model/Model.h"

Model::Model()
{
	m_db_path = "mw.db";
	is_initialized = false;
}

void Model::SetDatabasePath(std::string path)
{
	m_db_path = path;
}

bool Model::InitModel()
{
	if (is_initialized)
		return true;

	m_db_handler.CreateDB(this->m_db_path.c_str());
	InitUsersTable();
	InitProjectsTable();
	InitTasksTable();
	InitNotificationsTable();
	InitRemindersTable();
	InitPasswordsTable();
	InitAlertTimesTable();
	is_initialized = true;
	return true;
}

bool Model::AddUser(mw::User& user) 
{
	mw::Logger logger;

	try {
		// RAII for database connection
		if (!this->ConnectDataBase()) {
			logger.Error("Failed to connect to the database.");
			return false;
		}

		// Use parameterized query
		std::string sql = "INSERT INTO users(username, is_active, status, hashed_password, is_password_protected) "
			"VALUES (?, ?, ?, ?, ?);";

		logger.Info("Executing query: " + sql);

		sqlite3_stmt* statement;
		m_db_handler.Prepare(sql.c_str(), &statement);

		// Bind parameters
		sqlite3_bind_text(statement, 1, user.username.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(statement, 2, user.is_active);
		sqlite3_bind_int(statement, 3, user.status);
		sqlite3_bind_text(statement, 4, user.hashed_password.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(statement, 5, user.is_password_protected);

		// Execute the statement
		m_db_handler.Step(statement);
		m_db_handler.Finalize(statement);

		// Get the inserted user's uid
		sql = "SELECT last_insert_rowid() AS max_uid;";
		Records records;
		m_db_handler.Select(sql.c_str(), records);

		if (records.empty()) {
			logger.Error("Failed to retrieve the new user's uid.");
			this->DisconnectDb();
			return false;
		}

		user.uid = std::stoi(records[0][0]);

		// RAII for database disconnection
		if (!this->DisconnectDb()) {
			logger.Error("Failed to disconnect from the database.");
			return false;
		}

		return true;
	}
	catch (const std::exception& e) {
		logger.Error("Exception occurred: " + std::string(e.what()));
		this->DisconnectDb();
		return false;
	}
}

bool Model::AddProject(mw::Project& project) 
{
	mw::Logger logger;

	try {
		// RAII for database connection
		if (!this->ConnectDataBase()) {
			logger.Error("Failed to connect to the database.");
			return false;
		}

		// Use parameterized query
		std::string sql = "INSERT INTO projects(user_uid, name, start_time, is_active) "
			"VALUES (?, ?, ?, ?);";

		sqlite3_stmt* statement;
		m_db_handler.Prepare(sql.c_str(), &statement);

		// Bind parameters
		sqlite3_bind_int64(statement, 1, project.user_uid);
		sqlite3_bind_text(statement, 2, project.name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int64(statement, 3, project.start_time);
		sqlite3_bind_int(statement, 4, project.is_active);

		// Execute the statement
		m_db_handler.Step(statement);
		m_db_handler.Finalize(statement);

		// Get the inserted project's uid
		sql = "SELECT last_insert_rowid() AS max_uid;";
		Records records;
		m_db_handler.Select(sql.c_str(), records);

		if (records.empty()) {
			logger.Error("Failed to retrieve the new project's uid.");
			this->DisconnectDb();
			return false;
		}

		project.uid = std::stoi(records[0][0]);

		// RAII for database disconnection
		if (!this->DisconnectDb()) {
			logger.Error("Failed to disconnect from the database.");
			return false;
		}

		return true;
	}
	catch (const std::exception& e) {
		logger.Error("Exception occurred: " + std::string(e.what()));
		this->DisconnectDb();
		return false;
	}
}

bool Model::AddTask(mw::Task& task) {
	mw::Logger logger;

	try {
		task.StampLastUpdateTime();

		// Check if project UID is valid
		if (task.project_uid == 0) {
			throw std::runtime_error("Cannot add task with project_uid = 0");
		}

		// RAII for database connection
		if (!m_db_handler.Conn(this->m_db_path.c_str())) {
			logger.Error("Failed to connect to the database.");
			return false;
		}

		// Use parameterized query
		std::string sql = "INSERT INTO tasks(name, parent_uid, description, status, priority, start_time, deadline, project_uid, last_update, notification_enabled) "
			"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

		logger.Info("Executing query: " + sql);

		sqlite3_stmt* statement;
		m_db_handler.Prepare(sql.c_str(), &statement);

		// Bind parameters
		sqlite3_bind_text(statement, 1, task.name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int64(statement, 2, task.parent_uid);
		sqlite3_bind_text(statement, 3, task.description.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(statement, 4, task.status);
		sqlite3_bind_int(statement, 5, task.priority);
		sqlite3_bind_int64(statement, 6, task.creation_time);
		sqlite3_bind_int64(statement, 7, task.deadline);
		sqlite3_bind_int64(statement, 8, task.project_uid);
		sqlite3_bind_int64(statement, 9, task.last_update);
		sqlite3_bind_int(statement, 10, task.notification_enabled ? 1 : 0);

		// Execute the statement
		m_db_handler.Step(statement);
		m_db_handler.Finalize(statement);

		// Get the inserted task's uid
		sql = "SELECT last_insert_rowid() AS max_uid;";
		Records records;
		m_db_handler.Select(sql.c_str(), records);

		if (records.empty()) {
			logger.Error("Failed to retrieve the new task's uid.");
			m_db_handler.DisConn(this->m_db_path.c_str());
			return false;
		}

		task.uid = std::stoi(records[0][0]);

		// RAII for database disconnection
		if (!m_db_handler.DisConn(this->m_db_path.c_str())) {
			logger.Error("Failed to disconnect from the database.");
			return false;
		}

		return true;
	}
	catch (const std::exception& e) {
		logger.Error("Exception occurred: " + std::string(e.what()));
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::AddNotification(mw::Notification& notification) {
	mw::Logger logger;

	try {
		notification.StampLastUpdateTime();
		notification.Hash();

		// Check if user UID is valid
		if (notification.user_uid == 0) {
			throw std::runtime_error("Cannot add Notification with user UID = 0");
		}

		// RAII for database connection
		if (!m_db_handler.Conn(this->m_db_path.c_str())) {
			logger.Error("Failed to connect to the database.");
			return false;
		}

		// Use parameterized query to check for existing hash
		std::string sqlCheckHash = "SELECT * FROM notifications WHERE hash=?;";
		Records records;

		sqlite3_stmt* statement;
		m_db_handler.Prepare(sqlCheckHash.c_str(), &statement);
		sqlite3_bind_int64(statement, 1, notification.hash);

		//m_db_handler.SelectPrepared(statement, records);
		m_db_handler.Finalize(statement);

		if (!records.empty()) {
			// Notification with the same hash already exists
			if (!m_db_handler.DisConn(this->m_db_path.c_str())) {
				logger.Error("Failed to disconnect from the database.");
			}
			return true;
		}

		// Use parameterized query for inserting
		std::string sqlInsert = "INSERT INTO notifications(user_uid, hash, text, details, status, priority, repeat, start_time, end_time, last_update, ttl, color) "
			"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

		logger.Info("Executing query: " + sqlInsert);

		sqlite3_stmt* statementInsert;
		m_db_handler.Prepare(sqlInsert.c_str(), &statementInsert);

		// Bind parameters
		sqlite3_bind_int64(statementInsert, 1, notification.user_uid);
		sqlite3_bind_int64(statementInsert, 2, notification.hash);
		sqlite3_bind_text(statementInsert, 3, notification.text.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(statementInsert, 4, notification.details.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(statementInsert, 5, notification.status);
		sqlite3_bind_int(statementInsert, 6, notification.priority);
		sqlite3_bind_int(statementInsert, 7, notification.repeat);
		sqlite3_bind_int64(statementInsert, 8, notification.start_time);
		sqlite3_bind_int64(statementInsert, 9, notification.end_time);
		sqlite3_bind_int64(statementInsert, 10, notification.last_update);
		sqlite3_bind_int64(statementInsert, 11, notification.ttl);
		sqlite3_bind_int64(statementInsert, 12, notification.color);

		// Execute the statement
		m_db_handler.Step(statementInsert);
		m_db_handler.Finalize(statementInsert);

		// RAII for database disconnection
		if (!m_db_handler.DisConn(this->m_db_path.c_str())) {
			logger.Error("Failed to disconnect from the database.");
			return false;
		}

		return true;

	}
	catch (const std::exception& e) {
		logger.Error("Exception occurred: " + std::string(e.what()));
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::AddReminder(mw::Reminder& reminder) {
	mw::Logger logger;

	try {
		reminder.StampLastUpdateTime();
		reminder.Hash();

		// Check if user UID is valid
		if (reminder.user_uid == 0) {
			throw std::runtime_error("Cannot add Reminder with user UID = 0");
		}

		// RAII for database connection
		if (!m_db_handler.Conn(this->m_db_path.c_str())) {
			logger.Error("Failed to connect to the database.");
			return false;
		}

		// Use parameterized query
		std::string sql = "INSERT INTO reminders(user_uid, hash, title, text, status, priority, repeat, creation_time, reminder_time, end_time, last_update, color) "
			"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

		logger.Info("Executing query: " + sql);

		sqlite3_stmt* statement;
		m_db_handler.Prepare(sql.c_str(), &statement);

		// Bind parameters
		sqlite3_bind_int64(statement, 1, reminder.user_uid);
		sqlite3_bind_int64(statement, 2, reminder.hash);
		sqlite3_bind_text(statement, 3, reminder.title.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(statement, 4, reminder.text.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(statement, 5, reminder.status);
		sqlite3_bind_int(statement, 6, reminder.priority);
		sqlite3_bind_int(statement, 7, reminder.repeat);
		sqlite3_bind_int64(statement, 8, reminder.creation_time);
		sqlite3_bind_int64(statement, 9, reminder.reminder_time);
		sqlite3_bind_int64(statement, 10, reminder.end_time);
		sqlite3_bind_int64(statement, 11, reminder.last_update);
		sqlite3_bind_text(statement, 12, reminder.color.c_str(), -1, SQLITE_STATIC);

		// Execute the statement
		m_db_handler.Step(statement);
		m_db_handler.Finalize(statement);

		// RAII for database disconnection
		if (!m_db_handler.DisConn(this->m_db_path.c_str())) {
			logger.Error("Failed to disconnect from the database.");
			return false;
		}

		return true;
	}
	catch (const std::exception& e) {
		logger.Error("Exception occurred: " + std::string(e.what()));
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::AddPassword(mw::Password& password) {
	mw::Logger logger;

	try {
		password.StampLastUpdateTime();

		// Check if user UID is valid
		if (password.user_uid == 0) {
			throw std::runtime_error("Cannot add Password with user UID = 0");
		}

		// RAII for database connection
		if (!m_db_handler.Conn(this->m_db_path.c_str())) {
			logger.Error("Failed to connect to the database.");
			return false;
		}

		// Use parameterized query
		std::string sql = "INSERT INTO passwords(user_uid, username, encrypted_password, url, notes, creation_time, last_update) "
			"VALUES (?, ?, ?, ?, ?, ?, ?);";

		logger.Info("Executing query: " + sql);

		sqlite3_stmt* statement;
		m_db_handler.Prepare(sql.c_str(), &statement);

		// Bind parameters
		sqlite3_bind_int64(statement, 1, password.user_uid);
		sqlite3_bind_text(statement, 2, password.username.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(statement, 3, password.encrypted_password.c_str(), -1, SQLITE_STATIC);
		logger.EnableDebug();
		logger.Debug(password.encrypted_password);
		logger.DisableDebug();
		sqlite3_bind_text(statement, 4, password.url.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(statement, 5, password.notes.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int64(statement, 6, password.creation_time);
		sqlite3_bind_int64(statement, 7, password.last_update);

		// Execute the statement
		m_db_handler.Step(statement);
		m_db_handler.Finalize(statement);

		// RAII for database disconnection
		if (!m_db_handler.DisConn(this->m_db_path.c_str())) {
			logger.Error("Failed to disconnect from the database.");
			return false;
		}

		return true;

	}
	catch (const std::exception& e) {
		logger.Error("Exception occurred: " + std::string(e.what()));
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetActiveUser(mw::User& user)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		std::string sql = "SELECT * FROM users "
			              "WHERE is_active=1 "
			              "; ";
		Records records;

		m_db_handler.Select(sql.c_str(), records);
		if (records.empty())
		{
			m_db_handler.DisConn(this->m_db_path.c_str());
			return false;
		}
		Record row = records[0];
		user.uid = std::stoi(row[0]);
		user.username = row[1];
		user.is_active = std::stoi(row[2]) == 1 ? true : false;
		user.status = std::stoi(row[3]);
		user.hashed_password = row[4];
		user.is_password_protected = (bool)std::stoi(row[5]);
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		mw::Logger logger;
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::SetActiveUser(mw::User& user)
{
	try
	{
		this->ConnectDataBase();

		std::string sql = "UPDATE users "
					      "SET is_active=0 "
						  "WHERE is_active=1 "
						  ";";

		m_db_handler.Update(sql.c_str());

		sql = "UPDATE users "
			  "SET is_active=1 "
			  "WHERE uid=" + std::to_string(user.uid) +
			  ";";

		m_db_handler.Update(sql.c_str());
		this->DisconnectDb();

	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::DeleteTask(mw::Task& task)
{
	try
	{
		task.StampLastUpdateTime();
		this->ConnectDataBase();

		std::string sql = "DELETE FROM tasks WHERE uid=" + std::to_string(task.uid) + " ;";

		m_db_handler.ExeQuery(sql.c_str());

		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::DeleteReminder(mw::Reminder& reminder)
{
	try
	{
		reminder.StampLastUpdateTime();
		this->ConnectDataBase();

		std::string sql = "DELETE FROM reminders WHERE uid=" + std::to_string(reminder.uid) + " ;";

		m_db_handler.ExeQuery(sql.c_str());

		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}

}

bool Model::DeletePassword(mw::Password& password)
{
	try
	{
		this->ConnectDataBase();

		std::string sql = "DELETE FROM passwords WHERE uid=" + std::to_string(password.uid) + " ;";

		m_db_handler.ExeQuery(sql.c_str());

		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::ArchiveTask(mw::Task& task)
{
	try
	{
		task.StampLastUpdateTime();
		this->ConnectDataBase();

		std::string sql = "UPDATE tasks "
			"SET archived= 1 "
			"WHERE uid=" + std::to_string(task.uid) + " ;";
			

		m_db_handler.Update(sql.c_str());

		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::UnarchiveTask(mw::Task& task)
{
	try
	{
		task.StampLastUpdateTime();
		this->ConnectDataBase();

		std::string sql = "UPDATE tasks "
			"SET archived= 0 "
			"WHERE uid=" + std::to_string(task.uid) + " ;";


		m_db_handler.Update(sql.c_str());

		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::DeleteProject(mw::Project& project)
{
	try
	{
		mw::Logger logger;
		this->ConnectDataBase();

		std::string sql = "UPDATE projects "
			"SET status= " + std::to_string(mw::Project::ProjectStatus::DELETED) + ", "
			"is_active=0 " 
			"WHERE uid=" + std::to_string(project.uid) + " "
			";";
		m_db_handler.Update(sql.c_str());

		logger.Info(sql);

		m_db_handler.Update(sql.c_str());
		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::GetAllUsers(std::vector<mw::User>& ret_users_vect)
{
	try
	{
		this->ConnectDataBase();
		mw::Logger logger;
		Records records;
		Record row;
		mw::User user;
		std::string sql = "SELECT * FROM users;";
		m_db_handler.Select(sql.c_str(), records);
		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}
		for (int i = 0; i < records.size(); i++)
		{
			row = records[i];
			user.uid = std::stoi(row[0]);
			user.username = row[1];
			user.is_active = std::stoi(row[2]) == 1 ? true : false;
			user.status = std::stoi(row[3]);
			user.hashed_password = row[4];
			user.is_password_protected = (bool)std::stoi(row[5]);
			ret_users_vect.push_back(user);
		}
		this->DisconnectDb();
		return true;
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::GetActiveProject(mw::Project& project, mw::User& user)
{
	try
	{
		mw::Logger logger;
		
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		std::string sql = "SELECT * FROM projects "
			              "WHERE is_active=1 "
			              "AND user_uid=" + std::to_string(user.uid) +
			              ";";
		Records records;

		m_db_handler.Select(sql.c_str(), records);
		if (records.empty())
		{
			project.uid = 0;
			logger.Warning("No records were found for: " + sql);
			m_db_handler.DisConn(this->m_db_path.c_str());
			return false;
		}
		Record row = records[0];

		project.uid = std::stoi(row[0]);
		project.user_uid = std::stoi(row[1]);
		project.name = row[2];
		project.start_time = std::stoi(row[3]);
		project.is_active = std::stoi(row[4]) == 1 ? true : false;
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetAllProjects(std::vector<mw::Project>& projects_vect, const mw::User& user)
{
	mw::Logger logger;
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		logger.Info("selecting all projects for " + user.username);
		Records records;
		Record row;
		std::string sql = "SELECT * FROM projects WHERE user_uid=" + std::to_string(user.uid) + " "
			              "AND status!=-1 ;";
		logger.Info("Executinig query " + sql);
		m_db_handler.Select(sql.c_str(), records);
		mw::Project proj;
		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}
		for (int i = 0; i < records.size(); i++)
		{
			row = records[i];
			proj.uid = std::stoi(row[0]);
			proj.user_uid = std::stoi(row[1]);
			proj.name = row[2];
			proj.start_time = std::stoi(row[3]);
			proj.status = std::stoi(row[4]);
			proj.is_active = std::stoi(row[5]) == 1 ? true : false;
			projects_vect.push_back(proj);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch(const std::exception& e)
	{
		logger.Error("The exception is: " + std::string(e.what()));
		logger.Error("Exception occured at mwModel::GetAllProjects(std::vector<mwProject>& prjects_vect, const mwUser& user) ");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetAllNotifications(std::vector<mw::Notification>& notifications_vect, const mw::User& currnet_user)
{
	mw::Logger logger;
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		Records records;
		Record row;


		std::string sql = "SELECT * FROM notifications WHERE user_uid=" + std::to_string(currnet_user.uid) + " "
			"AND repeat>0 ;";


		m_db_handler.Select(sql.c_str(), records);

		mw::Notification notification;

		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}

		for (int i = 0; i < records.size(); i++)
		{
			row = records[i];
			notification.uid = std::stoi(row[0]);
			notification.user_uid = std::stoi(row[1]);
			notification.hash = std::stoull(row[2]);
			notification.text = row[3];
			notification.details = row[4];
			notification.status = (mw::NotificationStatus)std::stoi(row[5]);
			notification.priority = std::stoi(row[6]);
			notification.repeat = std::stoi(row[7]);
			notification.start_time = std::stoi(row[8]);
			notification.end_time = std::stoi(row[9]);
			notification.last_update = std::stoi(row[10]);
			notification.ttl = std::stoi(row[11]);
			notification.color = std::stoi(row[12]);

			notifications_vect.push_back(notification);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		logger.Error("Exception occured at mwModel::GetAllProjects(std::vector<mwProject>& prjects_vect, const mwUser& user) ");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetAllReminders(std::vector<mw::Reminder>& reminders, const mw::User& current_user)
{
	mw::Logger logger;
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		Records records;
		Record row;


		std::string sql = "SELECT * FROM reminders WHERE user_uid=" + std::to_string(current_user.uid) + " ;";


		m_db_handler.Select(sql.c_str(), records);


		mw::Reminder reminder;

		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}

		for (int i = 0; i < records.size(); i++)
		{

			row = records[i];
			reminder.uid = std::stoi(row[0]);
			reminder.user_uid = std::stoi(row[1]);
			reminder.hash = std::stoull(row[2]);
			reminder.title = row[3];
			reminder.text = row[4];
			reminder.status = (mw::ReminderStatus)std::stoi(row[5]);
			reminder.priority = std::stoi(row[6]);
			reminder.repeat = std::stoi(row[7]);
			reminder.creation_time = std::stoi(row[8]);
			reminder.reminder_time = std::stoi(row[9]);
			reminder.end_time = std::stoi(row[10]);
			reminder.last_update = std::stoi(row[11]);
			reminder.color = row[12];

			reminders.push_back(reminder);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		logger.Error("Exception occured at Model::GetAllReminders(std::vector<mw::Reminder>& reminders, const mw::User& current_user) ");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetAllPasswords(std::vector<mw::Password>& passwords, const mw::User& current_user)
{
	mw::Logger logger;
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		Records records;
		Record row;


		std::string sql = "SELECT * FROM passwords WHERE user_uid=" + std::to_string(current_user.uid) + " ;";


		m_db_handler.Select(sql.c_str(), records);


		mw::Password password;

		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}

		for (int i = 0; i < records.size(); i++)
		{

			row = records[i];
			password.uid = std::stoi(row[0]);
			password.user_uid = std::stoi(row[1]);
			password.username = row[2];
			password.encrypted_password = row[3];
			password.url = row[4];
			password.notes = row[5];
			password.creation_time = std::stoi(row[6]);
			password.last_update = std::stoi(row[7]);

			passwords.push_back(password);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		logger.Error("Exception occured at mwModel::GetAllProjects(std::vector<mwProject>& prjects_vect, const mwUser& user) ");
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::SetActiveProject(mw::Project& project)
{
	mw::Logger logger;
	try
	{
		this->ConnectDataBase();

		std::string sql = "UPDATE projects "
			              "SET is_active=0 "
			              "WHERE is_active=1 "
			              "AND user_uid=" + std::to_string(project.user_uid) +
			              ";";

		m_db_handler.Update(sql.c_str());

		sql = "UPDATE projects "
			  "SET is_active=1 "
			  "WHERE uid=" + std::to_string(project.uid) + " "
			  "AND user_uid= " + std::to_string(project.user_uid) +
			  ";";

		m_db_handler.Update(sql.c_str());
		this->DisconnectDb();
	}
	catch (...)
	{
		this->DisconnectDb();
		return false;
	}
}

bool Model::GetAllTasks(std::vector<mw::Task>& tasks, mw::Project& project)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		mw::Logger logger;
		logger.Info("selecting all tasks for " + project.name);
		Records records;
		Record row;
		std::string sql = "SELECT * FROM tasks WHERE project_uid=" + std::to_string(project.uid) + " "
						  "AND archived=0"
			              ";";
		logger.Info("Executinig query " + sql);
		m_db_handler.Select(sql.c_str(), records);
		mw::Task task;
		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}
		for (int i = 0; i < records.size(); i++)
		{
			row = records[i];
			task.uid = std::stoi(row[0]);
			task.parent_uid = std::stoi(row[1]);
			task.name = row[2];
			task.description = row[3];
			task.status = std::stoi(row[4]);
			task.priority = std::stoi(row[5]);
			task.creation_time = std::stoi(row[6]);
			task.end_time = std::stoi(row[7]);
			task.deadline = std::stoi(row[8]);
			task.last_update = std::stoi(row[9]);
			task.project_uid = std::stoi(row[10]);
			task.red = std::stoi(row[11]);
			task.green = std::stoi(row[12]);
			task.blue = std::stoi(row[13]);
			task.notification_enabled = (std::stoi(row[14]) == 1) ? true : false;
			tasks.push_back(task);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetArchiveAllTasks(std::vector<mw::Task>& tasks, mw::Project& project)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		mw::Logger logger;
		Records records;
		Record row;
		std::string sql = "SELECT * FROM tasks WHERE project_uid=" + std::to_string(project.uid) + " "
			"AND archived=1"
			";";		
		m_db_handler.Select(sql.c_str(), records);
		mw::Task task;
		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}
		for (int i = 0; i < records.size(); i++)
		{
			row = records[i];
			task.uid = std::stoi(row[0]);
			task.parent_uid = std::stoi(row[1]);
			task.name = row[2];
			task.description = row[3];
			task.status = std::stoi(row[4]);
			task.priority = std::stoi(row[5]);
			task.start_time = std::stoi(row[6]);
			task.end_time = std::stoi(row[7]);
			task.deadline = std::stoi(row[8]);
			task.last_update = std::stoi(row[9]);
			task.project_uid = std::stoi(row[10]);
			task.red = std::stoi(row[11]);
			task.green = std::stoi(row[12]);
			task.blue = std::stoi(row[13]);
			tasks.push_back(task);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::GetArchiveAllTasks(std::vector<mw::Task>& tasks, mw::Project& current_project, unsigned int num_of_days)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;
		auto current_epoch_time = std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()
			).count();

		mw::Logger logger;
		logger.Info("selecting all tasks for " + current_project.name);
		Records records;
		Record row;
		std::string sql = "SELECT * FROM tasks WHERE project_uid=" + std::to_string(current_project.uid) + " "
			"AND archived=1" + " "
			"AND last_update >= " + std::to_string(current_epoch_time - num_of_days*24*60*60) + " " 
			";";
		logger.Info("Executinig query " + sql);
		m_db_handler.Select(sql.c_str(), records);
		mw::Task task;
		if (records.empty())
		{
			logger.Warning("No records where found for: " + sql);
		}
		for (int i = 0; i < records.size(); i++)
		{
			row = records[i];
			task.uid = std::stoi(row[0]);
			task.parent_uid = std::stoi(row[1]);
			task.name = row[2];
			task.description = row[3];
			task.status = std::stoi(row[4]);
			task.priority = std::stoi(row[5]);
			task.start_time = std::stoi(row[6]);
			task.end_time = std::stoi(row[7]);
			task.deadline = std::stoi(row[8]);
			task.last_update = std::stoi(row[9]);
			task.project_uid = std::stoi(row[10]);
			task.red = std::stoi(row[11]);
			task.green = std::stoi(row[12]);
			task.blue = std::stoi(row[13]);
			tasks.push_back(task);
		}
		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return true;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::IsTaskFound(mw::Task& task)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		mw::Logger logger;
		Records records;
		bool found = true;
		std::string sql = "SELECT * FROM tasks WHERE uid=" + std::to_string(task.uid) + " "
		                  "AND archived=0"
			              ";";

		logger.Info("Executinig query " + sql);
		m_db_handler.Select(sql.c_str(), records);
		mw::Task task;
		if (records.empty())
			found = false;

		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return found;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::IsProjectFound(mw::Project& project)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		mw::Logger logger;
		Records records;
		bool found = true;
		std::string sql = "SELECT * FROM projects WHERE uid=" + std::to_string(project.uid) + " "
			              "AND status!=-1"
			              ";";

		logger.Info("Executinig query " + sql);
		m_db_handler.Select(sql.c_str(), records);
		mw::Task task;
		if (records.empty())
			found = false;

		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return found;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::IsUserFound(mw::User& user)
{
	try
	{
		if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
			return false;

		mw::Logger logger;
		Records records;
		bool found = true;
		std::string sql = "SELECT * FROM users WHERE uid=" + std::to_string(user.uid) + " ;";

		m_db_handler.Select(sql.c_str(), records);
		mw::Task task;
		if (records.empty())
			found = false;

		if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
			return false;
		return found;
	}
	catch (...)
	{
		m_db_handler.DisConn(this->m_db_path.c_str());
		return false;
	}
}

bool Model::UpdateTask(mw::Task& task) 
{
	mw::Logger logger;

	try {
		task.StampLastUpdateTime();

		if (task.project_uid == 0) {
			throw std::runtime_error("Cannot update task with project_uid=0");
		}

		// Use parameterized query
		std::string sql = "UPDATE tasks "
			"SET name=?, description=?, status=?, priority=?, deadline=?, last_update=?, notification_enabled=? "
			"WHERE uid=?;";

		// RAII for database connection
		if (!m_db_handler.Conn(this->m_db_path.c_str())) {
			logger.Error("Failed to connect to the database.");
			return false;
		}

		sqlite3_stmt* statement;
		m_db_handler.Prepare(sql.c_str(), &statement);

		// Bind parameters
		sqlite3_bind_text(statement, 1, task.name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(statement, 2, task.description.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(statement, 3, task.status);
		sqlite3_bind_int(statement, 4, task.priority);
		sqlite3_bind_int64(statement, 5, task.deadline);
		sqlite3_bind_int64(statement, 6, task.last_update);
		sqlite3_bind_int(statement, 7, task.notification_enabled ? 1 : 0);
		sqlite3_bind_int64(statement, 8, task.uid);

		// Execute the statement
		m_db_handler.Step(statement);
		m_db_handler.Finalize(statement);

		// Commit the transaction (if you are using transactions)
		// m_db_handler.Commit();

		// Disconnect in destructor (RAII)
				// RAII for database disconnection
		if (!m_db_handler.DisConn(this->m_db_path.c_str())) {
			logger.Error("Failed to disconnect from the database.");
			return false;
		}
		return true;
	}
	catch (const std::exception& e) {
		logger.Error("Exception occurred: " + std::string(e.what()));
		return false;
	}
}

bool Model::UpdateProject(mw::Project& project) 
{
	mw::Logger logger;

	try {
		// RAII for database connection
		if (!m_db_handler.Conn(this->m_db_path.c_str())) {
			logger.Error("Failed to connect to the database.");
			return false;
		}

		// Use parameterized query
		std::string sql = "UPDATE projects "
			"SET name=? "
			"WHERE uid=?;";

		logger.Info("Executing query: " + sql);

		sqlite3_stmt* statement;
		m_db_handler.Prepare(sql.c_str(), &statement);

		// Bind parameters
		sqlite3_bind_text(statement, 1, project.name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int64(statement, 2, project.uid);

		// Execute the statement
		m_db_handler.Step(statement);
		m_db_handler.Finalize(statement);

		// RAII for database disconnection
		if (!m_db_handler.DisConn(this->m_db_path.c_str())) {
			logger.Error("Failed to disconnect from the database.");
			return false;
		}

		return true;
	}
	catch (const std::exception& e) {
		logger.Error("Exception occurred: " + std::string(e.what()));
		return false;
	}
}

bool Model::UpdateUser(mw::User& user) 
{
	mw::Logger logger;

	try {
		// RAII for database connection
		if (!m_db_handler.Conn(this->m_db_path.c_str())) {
			logger.Error("Failed to connect to the database.");
			return false;
		}

		// Use parameterized query
		std::string sql = "UPDATE users "
			"SET username=?, status=?, hashed_password=? "
			"WHERE uid=?;";

		logger.Info("Executing query: " + sql);

		sqlite3_stmt* statement;
		m_db_handler.Prepare(sql.c_str(), &statement);

		// Bind parameters
		sqlite3_bind_text(statement, 1, user.username.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(statement, 2, user.status);
		sqlite3_bind_text(statement, 3, user.hashed_password.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int64(statement, 4, user.uid);

		// Execute the statement
		m_db_handler.Step(statement);
		m_db_handler.Finalize(statement);

		// RAII for database disconnection
		if (!m_db_handler.DisConn(this->m_db_path.c_str())) {
			logger.Error("Failed to disconnect from the database.");
			return false;
		}

		return true;
	}
	catch (const std::exception& e) {
		logger.Error("Exception occurred: " + std::string(e.what()));
		return false;
	}
}

bool Model::UpdateNotification(mw::Notification& notification) {
	mw::Logger logger;

	try {
		notification.StampLastUpdateTime();

		// RAII for database connection
		if (!m_db_handler.Conn(this->m_db_path.c_str())) {
			logger.Error("Failed to connect to the database.");
			return false;
		}

		// Use parameterized query
		std::string sql = "UPDATE notifications "
			"SET text=?, details=?, status=?, priority=?, repeat=?, "
			"end_time=?, last_update=?, ttl=?, color=? "
			"WHERE uid=?;";

		logger.Info("Executing query: " + sql);

		sqlite3_stmt* statement;
		m_db_handler.Prepare(sql.c_str(), &statement);

		// Bind parameters
		sqlite3_bind_text(statement, 1, notification.text.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(statement, 2, notification.details.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(statement, 3, notification.status);
		sqlite3_bind_int(statement, 4, notification.priority);
		sqlite3_bind_int(statement, 5, notification.repeat);
		sqlite3_bind_int64(statement, 6, notification.end_time);
		sqlite3_bind_int64(statement, 7, notification.last_update);
		sqlite3_bind_int64(statement, 8, notification.ttl);
		sqlite3_bind_int64(statement, 9, notification.color);
		sqlite3_bind_int64(statement, 10, notification.uid);

		// Execute the statement
		m_db_handler.Step(statement);
		m_db_handler.Finalize(statement);

		// RAII for database disconnection
		if (!m_db_handler.DisConn(this->m_db_path.c_str())) {
			logger.Error("Failed to disconnect from the database.");
			return false;
		}

		return true;
	}
	catch (const std::exception& e) {
		logger.Error("Exception occurred: " + std::string(e.what()));
		return false;
	}
}

bool Model::ConnectDataBase()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		throw "Failed to connect to DB ";
	return true;
}

bool Model::DisconnectDb()
{
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitUsersTable()
{
	mw::Logger logger;
	logger.Info("Initialzing users table");
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"users\" ( "
					"\"uid\"	INTEGER NOT NULL UNIQUE, "
					"\"username\"	TEXT NOT NULL, "
					"\"is_active\"  NUMERIC NOT NULL DEFAULT 0, "
             		"\"status\"     NUMERIC NOT NULL DEFAULT 0, "
					"\"hashed_password\" TEXT NOT NULL, "
					"\"is_password_protected\" NUMERIC NOT NULL DEFAULT 0, "
					"PRIMARY KEY(\"uid\" AUTOINCREMENT) "
					"); "

					"INSERT OR IGNORE INTO \"users\" ( "
		            "\"uid\", "
					"\"username\", "
					"\"is_active\", "
                    "\"status\" , "
					"\"hashed_password\" , "
					"\"is_password_protected\")"
					"VALUES ( "
		            "\"1\", "
					"\"Default User\", "
					"\"1\", "
		            "\"0\" , "
					"\"$2a$12$U8YKViISROZEWkabHvseXujY64NhQxpvklgek20SDClb2yP7oK.kW\" , "
		            "\"0\" ); ";

	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitProjectsTable()
{
	mw::Logger logger;
	logger.Info("Initialzing projects table");
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"projects\" (    "
				      "\"uid\"	        INTEGER NOT NULL UNIQUE,    "
		              "\"user_uid\"	    INTEGER NOT NULL DEFAULT 1, "
				      "\"name\"	        TEXT,                       "
				      "\"start_time\"   INTEGER,                    "
                	  "\"status\"       INTEGER NOT NULL DEFAULT 0, "
                      "\"is_active\"	NUMERIC NOT NULL DEFAULT 0, "
                      "PRIMARY KEY(\"uid\" AUTOINCREMENT)           "
				      ")";
	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitTasksTable()
{
	mw::Logger logger;
	logger.Info("Initialzing tasks table");
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql =  "CREATE TABLE IF NOT EXISTS \"tasks\" (      "
					   "\"uid\"	INTEGER NOT NULL UNIQUE,            "
                	   "\"parent_uid\"	INTEGER DEFAULT 0,          "
					   "\"name\"	    TEXT,                       "
					   "\"description\"	TEXT,                       "
                	   "\"status\"	    INTEGER DEFAULT 0,          "
                	   "\"priority\"	INTEGER DEFAULT 2,          "
					   "\"start_time\"	INTEGER NOT NULL,           "
					   "\"end_time\"	INTEGER DEFAULT 0,          "
		               "\"deadline\"	INTEGER DEFAULT 0,          "
		               "\"last_update\"	INTEGER DEFAULT 0,          "
					   "\"project_uid\"	INTEGER DEFAULT 1,          "
                	   "\"red\"	        INTEGER DEFAULT 0,          "
		               "\"green\"	    INTEGER DEFAULT 0,          "
		               "\"blue\"	    INTEGER DEFAULT 0,          "
					   "\"notification_enabled\" BOLLEAN DEFAULT 1, "
					   "\"archived\"	INTEGER DEFAULT 0,          "
					   "PRIMARY KEY(\"uid\" AUTOINCREMENT)          "
					   ")";
	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();

	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitNotificationsTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"notifications\" (      "
						"\"uid\"	        INTEGER NOT NULL UNIQUE,       "
						"\"user_uid\"	    INTEGER NOT NULL DEFAULT 1,    "
						"\"hash\"	        BIGINT NOT NULL DEFAULT 0,    "
						"\"text\"	        TEXT,                          "
		                "\"details\"	    TEXT NOT NULL ,    "
						"\"status\"	        INTEGER NOT NULL DEFAULT 0,    "
						"\"priority\"	    INTEGER NOT NULL DEFAULT 2,    "
		                "\"repeat\"	        INTEGER NOT NULL DEFAULT 1,    "
						"\"start_time\"	    INTEGER NOT NULL,              "
						"\"end_time\"	    INTEGER NOT NULL DEFAULT 0,    "
                 		"\"last_update\"	INTEGER NOT NULL DEFAULT 0,    "
						"\"ttl\"	        INTEGER NOT NULL DEFAULT 0,    "
						"\"color\"	        INTEGER DEFAULT -1,            "
						"PRIMARY KEY(\"uid\" AUTOINCREMENT)                "
						")";
	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitRemindersTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"reminders\" (      "
		"\"uid\"	         INTEGER NOT NULL UNIQUE,       "
		"\"user_uid\"	     INTEGER NOT NULL DEFAULT 1,    "
		"\"hash\"	         BIGINT NOT NULL DEFAULT 0,     "
		"\"title\"	         TEXT NOT NULL ,                "
		"\"text\"	         TEXT,                          "
		"\"status\"	         INTEGER NOT NULL DEFAULT 0,    "
		"\"priority\"	     INTEGER NOT NULL DEFAULT 2,    "
		"\"repeat\"	         INTEGER NOT NULL DEFAULT 1,    "
		"\"creation_time\"	 INTEGER NOT NULL,              "
		"\"reminder_time\"	 INTEGER NOT NULL,              "
		"\"end_time\"	     INTEGER NOT NULL DEFAULT 0,    "
		"\"last_update\"	 INTEGER NOT NULL DEFAULT 0,    "
		"\"color\"	         TEXT DEFAULT '#FFFFFF',        "
		"PRIMARY KEY(\"uid\" AUTOINCREMENT)                 "
		")";
	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitPasswordsTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"passwords\" (      "
		"\"uid\"	            INTEGER NOT NULL UNIQUE,    "
		"\"user_uid\"	        INTEGER NOT NULL DEFAULT 1, "
		"\"username\"	        TEXT NOT NULL,              "
		"\"encrypted_password\" TEXT NOT NULL ,             "
		"\"url\"	            TEXT,                       "
		"\"notes\"	            TEXT,                       "
		"\"creation_time\"	 INTEGER NOT NULL,              "
		"\"last_update\"	 INTEGER NOT NULL DEFAULT 0,    "
		"PRIMARY KEY(\"uid\" AUTOINCREMENT)                 "
		")";
	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}

bool Model::InitAlertTimesTable()
{
	if (m_db_handler.Conn(this->m_db_path.c_str()) == false)
		return false;

	const char* sql = "CREATE TABLE IF NOT EXISTS \"reminder_alert_times\" (      "
		"\"uid\"	INTEGER NOT NULL UNIQUE,"
		"\"reminder_uid\"	    INTEGER NOT NULL,"
		"\"value\"              INTEGER NOT NULL,"
		"PRIMARY KEY(\"uid\" AUTOINCREMENT)"
		");";

	m_mutex.lock();
	m_db_handler.ExeQuery(sql);
	m_mutex.unlock();
	if (m_db_handler.DisConn(this->m_db_path.c_str()) == false)
		return false;
	return true;
}
