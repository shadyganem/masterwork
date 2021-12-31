#include "controller\mwController.h"

void mwController::Init()
{
	m_logger.Info("---------------------------------------------------------------------------");
	m_logger.Info("Intializing controller");
	m_model.SetDbPath("mw.db");
	m_model.InitModel();
	m_model.GetActiveUser(m_active_user);
	m_model.GetActiveProject(m_active_project, m_active_user);
	m_logger.Info("The active user is \"" + this->m_active_user.username + "\"");
	m_logger.Info("The active project is \"" + this->m_active_project.name + "\"");
}

bool mwController::Search(wxString& search_query)
{
	return false;
}

wxString mwController::GetActiveUsername(void)
{
	return wxString(this->m_active_user.username);
}

void mwController::GetActiveProject(mwProject& project)
{
	m_model.GetActiveUser(m_active_user);
	m_model.GetActiveProject(m_active_project, m_active_user);
	if (m_active_project.uid == 0)
		this->m_is_project_selected = false;
	else
		this->m_is_project_selected = true;
	project = m_active_project;
}

void mwController::SetActiveUser(int user_uid)
{
	mwUser user;
	user.uid = user_uid;
	this->m_model.SetActiveUser(user);
}

void mwController::SetActiveProject(mwProject& project)
{
	m_model.GetActiveUser(m_active_user);
	this->m_model.SetActiveProject(project);
	m_model.GetActiveProject(m_active_project, m_active_user);
	PostUpdateUI(WORK_PANEL_ID);
}

void mwController::SetStatusBarText(const wxString& txt)
{
	m_mutex.Lock();
	m_status_bar_text = txt;
	m_mutex.Unlock();
	PostUpdateUI(MAIN_FRAME_ID);
}

wxString mwController::GetStatusBarText(void)
{
	return m_status_bar_text;
}

void mwController::SetInfoBarText(const wxString& txt)
{
	m_mutex.Lock();
	m_info_bar_text = txt;
	m_mutex.Unlock();
	PostNotification(MAIN_FRAME_ID);
}

wxString mwController::GetInfoBarText(void)
{
	return this->m_info_bar_text;
}

void mwController::RegisterMainFrame(wxEvtHandler* mf)
{
	m_main_frame = mf;
}

void mwController::RegisterEventHandler(int id, wxEvtHandler* event_handler)
{
	mwLogger logger;
	if (id != wxID_ANY)
	{
		this->m_event_handlers[id] = event_handler;
	}
	else
	{
		logger.Warning("Can not register event handlers without a unique ID");
	}
}

void mwController::AddTask(std::string name, std::string dec)
{

	mwTask task(name, dec);
	task.StampCreationTime();
	m_mutex.Lock();
	m_model.AddTask(task);
	m_mutex.Unlock();
	PostUpdateUI(MAIN_FRAME_ID);
}

void mwController::DeleteTask(mwTask& task)
{
	mwLogger logger;
	logger.Info("deleting task: " + std::to_string(task.uid));
	m_model.DeleteTask(task);
	m_model.GetActiveUser(m_active_user);
	m_model.GetActiveProject(m_active_project, m_active_user);
	PostUpdateUI(WORK_PANEL_ID);
}

void mwController::DeleteProject(mwProject& project)
{
	mwLogger logger;
	logger.Info("deleting project: " + std::to_string(project.uid));
	m_model.DeleteProject(project);
	m_model.GetActiveUser(m_active_user);
	m_model.GetActiveProject(m_active_project, m_active_user);
	PostUpdateUI(WORK_PANEL_ID);
	PostUpdateUI(SIDE_PANEL_ID);
}

void mwController::AddTask(mwTask& task)
{
	m_mutex.Lock();
	if (m_model.IsTaskFound(task))
	{
		m_mutex.Lock();
		m_model.UpdateTask(task);
	}
	else
	{
		m_model.AddTask(task);
	}
	m_mutex.Unlock();
	PostUpdateUI(MAIN_FRAME_ID);
	PostUpdateUI(WORK_PANEL_ID);
}

void mwController::AddProject(mwProject& project)
{
	m_model.GetActiveUser(m_active_user);
	project.user_uid = m_active_user.uid;
	project.is_active = 0;
	m_mutex.Lock();
	m_model.AddProject(project);
	m_mutex.Unlock();
	PostUpdateUI(SIDE_PANEL_ID);
}

void mwController::GetProjectsForActiveUser(std::vector<std::string>& projects)
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

void mwController::GetProjectsForActiveUser(std::vector<mwProject>& projects)
{
	this->m_model.GetActiveUser(m_active_user);
	this->m_model.GetAllProjects(projects, m_active_user);
}

void mwController::GetTasksForActiveProject(std::vector<mwTask>& tasks)
{
	m_model.GetActiveUser(m_active_user);
	m_model.GetActiveProject(m_active_project, m_active_user);
	this->m_model.GetAllTasks(tasks, m_active_project);
}

void mwController::PostUpdateUI(int wind_id)
{
	mwLogger logger;
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

void mwController::PostNotification(int windId)
{
	wxCommandEvent* event = new wxCommandEvent(mwNotification, windId);
	event->SetEventObject(this->m_main_frame);
	this->m_main_frame->QueueEvent(event);
}