#include "controller\mwController.h"

bool mwController::RegisterView()
{
	return false;
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
}

wxString mwController::GetStatusBarText(void)
{
	return m_status_bar_text;
}

void mwController::RegisterEvtHandler(wxEvtHandler* evt_handler)
{
	m_events_handlers.push_back(evt_handler);
}
