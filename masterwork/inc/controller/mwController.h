#pragma once

#include "wx/wx.h"
#include <wx/thread.h>
#include <wx/event.h>

class mwController
{
public:
	mwController(const mwController&) = delete;
	static mwController& Get()
	{
		static mwController instance;
		return instance;
	}
	// mwController interface
	bool RegisterView();
	bool Search(wxString& search_query);
	void SetStatusBarText(const wxString& txt);
	wxString GetStatusBarText(void);
	void RegisterEvtHandler(wxEvtHandler*);
private:
	mwController() {}
	wxVector <wxEvtHandler*> m_events_handlers;
	wxString m_status_bar_text;
	#include <wx/thread.h>
	wxMutex m_mutex;
};

