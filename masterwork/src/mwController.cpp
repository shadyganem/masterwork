#include "controller\mwController.h"

void mwController::Init()
{
	m_logger.Info("---------------------------------------------------------------------------");
	m_logger.Info("Intializing controller");
	m_model.SetDbPath("mw.db");
	m_model.InitModel();
}

bool mwController::Search(wxString& search_query)
{
	return false;
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

