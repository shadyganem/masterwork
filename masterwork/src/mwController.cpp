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
	m_logger.Info("The active project is \"" + this->m_active_project.project_name + "\"");
	mwProject project;
	project.uid = 2;
	project.user_uid = 2;
	m_model.SetActiveProject(project);
}

bool mwController::Search(wxString& search_query)
{
	return false;
}

wxString mwController::GetActiveUsername(void)
{
	return wxString(this->m_active_user.username);
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

void mwController::AddTask(std::string name, std::string dec)
{
	mwTask task(name, dec);
	task.StampCreationTime();
	m_mutex.Lock();
	m_model.AddTask(task);
	m_mutex.Unlock();
	PostUpdateUI(MAIN_FRAME_ID);
}

void mwController::GetProjectsForActiveUser(std::vector<std::string>& projects)
{
	mwLogger logger;
	logger.Info("at GetPorjectsForCurrentUser");
	m_model.GetActiveUser(m_active_user);
	std::vector<mwProject> mw_projects;
	m_model.GetAllProjects(mw_projects, m_active_user);
	std::vector<mwProject>::iterator it;
	for (it = mw_projects.begin(); it != mw_projects.end(); ++it)
	{
		projects.push_back(it->project_name);
	}
}

void mwController::PostUpdateUI(int windId)
{
	wxCommandEvent* event = new wxCommandEvent(mwUpdateUI, windId);
	event->SetEventObject(this->m_main_frame);
	this->m_main_frame->QueueEvent(event);
}

void mwController::PostNotification(int windId)
{
	wxCommandEvent* event = new wxCommandEvent(mwNotification, windId);
	event->SetEventObject(this->m_main_frame);
	this->m_main_frame->QueueEvent(event);
}