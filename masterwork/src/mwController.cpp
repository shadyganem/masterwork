#include "controller\mwController.h"

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

