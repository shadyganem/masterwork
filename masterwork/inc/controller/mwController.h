#pragma once

#include "wx/wx.h"
#include <wx/thread.h>
#include <wx/event.h>
#include "mwDefines.h"
#include "model/mwModel.h"
#include "model/mwTask.h"
#include "model/mwUser.h"
#include "controller/mwLogger.h"

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
	void Init();
	bool Search(wxString& search_query);
	void SetStatusBarText(const wxString& txt);
	wxString GetStatusBarText(void);
	void SetInfoBarText(const wxString& txt);
	wxString GetInfoBarText(void);
	void RegisterMainFrame(wxEvtHandler* mf);
	void AddTask(std::string name, std::string dec);

private:
	mwController() {}
	void PostUpdateUI(int windId);
	void PostNotification(int windId);
	wxEvtHandler* m_main_frame;
	wxVector <wxEvtHandler*> m_events_handlers;
	wxString m_status_bar_text;
	wxString m_info_bar_text;
	mwModel m_model;
	wxMutex m_mutex;
	mwUser m_current_user;
	mwProject m_current_project;
	mwLogger m_logger;
	mwUser current_user;
};

