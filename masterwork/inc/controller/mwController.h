#pragma once

#include "wx/wx.h"
#include <wx/thread.h>
#include <wx/event.h>
#include "mwDefines.h"

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
	bool Search(wxString& search_query);
	void SetStatusBarText(const wxString& txt);
	wxString GetStatusBarText(void);
	void SetInfoBarText(const wxString& txt);
	wxString GetInfoBarText(void);
	void RegisterMainFrame(wxEvtHandler* mf);

private:
	mwController() {}
	void PostUpdateUI(int windId);
	void PostNotification(int windId);
	wxEvtHandler* m_main_frame;
	wxVector <wxEvtHandler*> m_events_handlers;
	wxString m_status_bar_text;
	wxString m_info_bar_text;

	wxMutex m_mutex;
};

