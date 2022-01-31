#include "controller\Controller.h"

void mw::Controller::Init()
{
	m_logger.Clear();
	m_logger.Disable();
	m_logger.Info("Intializing controller");
	m_model.SetDbPath("mw.db");
	m_model.InitModel();
	m_model.GetActiveUser(m_active_user);
	m_model.GetActiveProject(m_active_project, m_active_user);
	m_logger.Info("The active user is \"" + this->m_active_user.username + "\"");
	m_logger.Info("The active project is \"" + this->m_active_project.name + "\"");
	m_num_of_notifications = 0;
	m_active_winid = TASKS_WINDOW_ID;
}

bool mw::Controller::Search(wxString& search_query)
{
	return false;
}

wxString mw::Controller::GetActiveUsername(void)
{
	return wxString(this->m_active_user.username);
}

void mw::Controller::GetActiveProject(mwProject& project)
{
	m_model.GetActiveUser(m_active_user);
	m_model.GetActiveProject(m_active_project, m_active_user);
	if (m_active_project.uid == 0)
		this->m_is_project_selected = false;
	else
		this->m_is_project_selected = true;
	project = m_active_project;
}

void mw::Controller::SetActiveUser(int user_uid)
{
	User user;
	user.uid = user_uid;
	this->m_model.SetActiveUser(user);
}

void mw::Controller::SetActiveUser(mw::User& user, bool post_update_ui)
{
	this->m_model.SetActiveUser(user);
	if (post_update_ui)
	{
		PostUpdateUI(MAIN_FRAME_ID);
		PostUpdateUI(SIDE_PANEL_ID);
		PostUpdateUI(TASKS_WINDOW_ID);
		PostUpdateUI(ARCHIVE_WINDOW_ID);
		PostUpdateUI(NOTIFICATIONS_WINDOW_ID);
	}
}

void mw::Controller::SetActiveProject(mwProject& project, bool post_update_ui)
{
	this->m_mutex.Lock();
	this->m_model.GetActiveUser(m_active_user);
	this->m_model.SetActiveProject(project);
	this->m_model.GetActiveProject(m_active_project, m_active_user);
	this->m_mutex.Unlock();
	if (post_update_ui)
	{
		PostUpdateUI(SIDE_PANEL_ID);
		PostUpdateUI(TASKS_WINDOW_ID);
		PostUpdateUI(ARCHIVE_WINDOW_ID);
	}
}

void mw::Controller::SetStatusBarText(const wxString& txt)
{
	m_mutex.Lock();
	m_status_bar_text = txt;
	m_mutex.Unlock();
	PostUpdateUI(MAIN_FRAME_ID);
}

wxString mw::Controller::GetStatusBarText(void)
{
	return m_status_bar_text;
}

void mw::Controller::SetInfoBarText(const wxString& txt)
{
	m_mutex.Lock();
	m_info_bar_text = txt;
	m_mutex.Unlock();
	PostNotification(MAIN_FRAME_ID);
}

wxString mw::Controller::GetInfoBarText(void)
{
	return this->m_info_bar_text;
}

void mw::Controller::RegisterMainFrame(wxEvtHandler* mf)
{
	m_main_frame = mf;
}

void mw::Controller::RegisterEventHandler(int id, wxEvtHandler* event_handler)
{
	Logger logger;
	if (id != wxID_ANY)
	{
		this->m_event_handlers[id] = event_handler;
	}
	else
	{
		logger.Warning("Can not register event handlers without a unique ID");
	}
}

void mw::Controller::AddTask(std::string name, std::string dec)
{
	Task task(name, dec);
	task.StampCreationTime();
	task.StampLastUpdateTime();
	m_mutex.Lock();
	m_model.AddTask(task);
	m_mutex.Unlock();
	PostUpdateUI(MAIN_FRAME_ID);
}

void mw::Controller::DeleteTask(Task& task)
{
	task.StampLastUpdateTime();
	m_model.DeleteTask(task);
	m_model.GetActiveUser(m_active_user);
	m_model.GetActiveProject(m_active_project, m_active_user);
	PostUpdateUI(TASKS_WINDOW_ID);
	PostUpdateUI(ARCHIVE_WINDOW_ID);
}

void mw::Controller::UnArchiveTask(Task& task)
{
	m_mutex.Lock();
	task.status = mw::Task::TaskStatus::NOTSTARTED;
	m_model.UpdateTask(task);
	m_mutex.Unlock();
	PostUpdateUI(MAIN_FRAME_ID);
	PostUpdateUI(TASKS_WINDOW_ID);
	PostUpdateUI(ARCHIVE_WINDOW_ID);
}

void mw::Controller::DeleteProject(mwProject& project)
{
	m_model.DeleteProject(project);
	m_model.GetActiveUser(m_active_user);
	m_model.GetActiveProject(m_active_project, m_active_user);
	PostUpdateUI(TASKS_WINDOW_ID);
	PostUpdateUI(ARCHIVE_WINDOW_ID);
	PostUpdateUI(SIDE_PANEL_ID);
}

void mw::Controller::AddTask(Task& task)
{
	m_mutex.Lock();
	if (m_model.IsTaskFound(task))
	{
		m_model.UpdateTask(task);
	}
	else
	{
		m_model.AddTask(task);
	}
	m_mutex.Unlock();
	PostUpdateUI(MAIN_FRAME_ID);
	PostUpdateUI(TASKS_WINDOW_ID);
	PostUpdateUI(ARCHIVE_WINDOW_ID);
}

void mw::Controller::AddProject(mwProject& project, bool post_update_ui)
{
	m_model.GetActiveUser(m_active_user);
	project.user_uid = m_active_user.uid;
	project.is_active = 0;
	m_mutex.Lock();
	if (m_model.IsProjectFound(project))
	{
		m_model.UpdateProject(project);
	}
	else
	{
		m_model.AddProject(project);
	}
	m_mutex.Unlock();
	if (post_update_ui)
	{
		PostUpdateUI(SIDE_PANEL_ID);
	}
}

void mw::Controller::AddNotification(mw::Notification& notification, bool post_update_ui)
{
	m_model.GetActiveUser(m_active_user);
	notification.user_uid = m_active_user.uid;
	m_mutex.Lock();
	m_model.AddNotification(notification);
	m_mutex.Unlock();
	if (post_update_ui)
	{
		PostUpdateUI(MAIN_FRAME_ID);
		PostUpdateUI(NOTIFICATIONS_WINDOW_ID);
	}
}

void mw::Controller::AddUser(mw::User& user, bool set_active, bool post_update_ui)
{
	m_mutex.Lock();
	if (m_model.IsUserFound(user))
	{
		m_model.UpdateUser(user);
	}
	else
	{
		m_model.AddUser(user);
	}
	if (set_active == true)
	{
		this->SetActiveUser(user, false);
		this->m_model.UpdateUser(m_active_user);
	}
	m_mutex.Unlock();
	if (post_update_ui)
	{
		PostUpdateUI(SIDE_PANEL_ID);
		PostUpdateUI(TASKS_WINDOW_ID);
		PostUpdateUI(ARCHIVE_WINDOW_ID);
		PostUpdateUI(NOTIFICATIONS_WINDOW_ID);
		PostUpdateUI(MAIN_FRAME_ID);
	}
}

void mw::Controller::GetAllUsers(std::vector<mw::User>& users)
{
	m_model.GetAllUsers(users);
}

void mw::Controller::GetProjectsForActiveUser(std::vector<std::string>& projects)
{
	m_model.GetActiveUser(m_active_user);
	std::vector<mwProject> mw_projects;
	m_model.GetAllProjects(mw_projects, m_active_user);
	std::vector<mwProject>::iterator it;
	for (it = mw_projects.begin(); it != mw_projects.end(); ++it)
	{
		projects.push_back(it->name);
	}
}

void mw::Controller::GetProjectsForActiveUser(std::vector<mwProject>& projects)
{
	this->m_model.GetActiveUser(m_active_user);
	this->m_model.GetAllProjects(projects, m_active_user);
}

void mw::Controller::GetNotificationsForActiveUser(std::vector<mw::Notification>& notifications)
{
	this->m_model.GetActiveUser(m_active_user);
	this->m_model.GetAllNotifications(notifications, m_active_user);
}

void mw::Controller::GetTasksForActiveProject(std::vector<Task>& tasks)
{
	m_model.GetActiveUser(m_active_user);
	m_model.GetActiveProject(m_active_project, m_active_user);
	this->m_model.GetAllTasks(tasks, m_active_project);
}

void mw::Controller::GetArchiveTasksForActiveProject(std::vector<Task>& tasks)
{
	m_model.GetActiveUser(m_active_user);
	m_model.GetActiveProject(m_active_project, m_active_user);
	this->m_model.GetArchiveAllTasks(tasks, m_active_project);
}

void mw::Controller::RequestUpdateUI(int wind_id)
{
	this->PostUpdateUI(wind_id);
}

void mw::Controller::SetActiveWindow(int winid)
{
	m_active_winid = winid;
}

int mw::Controller::GetNumOfNotifications(int& num, bool poll)
{
	if (poll)
	{
		std::vector<mw::Notification> vect;
		this->GetNotificationsForActiveUser(vect);
		m_num_of_notifications = vect.size();
	}
	num = m_num_of_notifications;
	return num;
}

void mw::Controller::PostUpdateUI(int wind_id)
{
	Logger logger;
	if (this->m_event_handlers.count(wind_id) != 0)
	{
		wxEvtHandler* event_handler = this->m_event_handlers[wind_id];
		wxCommandEvent* event = new wxCommandEvent(mwUpdateUI, wind_id);
		event->SetEventObject(event_handler);
		event_handler->QueueEvent(event);
	}
	else
	{
		logger.Info("No event handler found for WindId = " + std::to_string(wind_id));
	}
}

void mw::Controller::PostNotification(int windId)
{
	wxCommandEvent* event = new wxCommandEvent(mwNotification, windId);
	event->SetEventObject(this->m_main_frame);
	this->m_main_frame->QueueEvent(event);
}