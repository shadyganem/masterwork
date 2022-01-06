#pragma once

#include "wx/wx.h"
#include <wx/thread.h>
#include <wx/event.h>
#include "mwDefines.h"
#include "model/mwModel.h"
#include "model/mwTask.h"
#include "model/mwUser.h"
#include "controller/mwLogger.h"
#include <vector>
#include <map>

namespace mw
{
	class Controller
	{
	public:
		Controller(const Controller&) = delete;
		static Controller& Get()
		{
			static Controller instance;
			return instance;
		}
		// mwController interface
		void Init();
		bool Search(wxString& search_query);
		wxString GetActiveUsername(void);
		void GetActiveProject(mwProject& project);
		void SetActiveUser(int user_uid);
		void SetActiveProject(mwProject& project);
		void SetStatusBarText(const wxString& txt);
		wxString GetStatusBarText(void);
		void SetInfoBarText(const wxString& txt);
		wxString GetInfoBarText(void);
		void RegisterMainFrame(wxEvtHandler* mf);
		void RegisterEventHandler(int ID, wxEvtHandler* event_handler);
		void AddTask(std::string name, std::string dec);
		void DeleteTask(mwTask& task);
		void DeleteProject(mwProject& project);
		void AddTask(mwTask& task);
		void AddProject(mwProject& project);
		void GetProjectsForActiveUser(std::vector<std::string>& projects);
		void GetProjectsForActiveUser(std::vector<mwProject>& projects);
		void GetTasksForActiveProject(std::vector<mwTask>& tasks);

	private:
		Controller() {}
		void PostUpdateUI(int windId);
		void PostNotification(int windId);
		wxEvtHandler* m_main_frame;
		wxVector <wxEvtHandler*> m_events_handlers;
		std::map<int, wxEvtHandler*> m_event_handlers;
		wxString m_status_bar_text;
		wxString m_info_bar_text;
		mwModel m_model;
		wxMutex m_mutex;
		mwProject m_current_project;
		mwLogger m_logger;
		mwUser m_active_user;
		mwProject m_active_project;
		std::map<int, mwTask> m_seen_tasks;
		bool m_is_project_selected;
	};
}

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
	wxString GetActiveUsername(void);
	void GetActiveProject(mwProject& project);
	void SetActiveUser(int user_uid);
	void SetActiveProject(mwProject& project);
	void SetStatusBarText(const wxString& txt);
	wxString GetStatusBarText(void);
	void SetInfoBarText(const wxString& txt);
	wxString GetInfoBarText(void);
	void RegisterMainFrame(wxEvtHandler* mf);
	void RegisterEventHandler(int ID, wxEvtHandler* event_handler);
	void AddTask(std::string name, std::string dec);
	void DeleteTask(mwTask& task);
	void DeleteProject(mwProject& project);
	void AddTask(mwTask& task);
	void AddProject(mwProject& project);
	void GetProjectsForActiveUser(std::vector<std::string>& projects);
	void GetProjectsForActiveUser(std::vector<mwProject>& projects);
	void GetTasksForActiveProject(std::vector<mwTask>& tasks);
	void RequestUpdateUI(int wind_id);

private:
	mwController() {}
	void PostUpdateUI(int windId);
	void PostNotification(int windId);
	wxEvtHandler* m_main_frame;
	wxVector <wxEvtHandler*> m_events_handlers;
	std::map<int, wxEvtHandler*> m_event_handlers;
	wxString m_status_bar_text;
	wxString m_info_bar_text;
	mwModel m_model;
	wxMutex m_mutex;
	mwProject m_current_project;
	mwLogger m_logger;
	mwUser m_active_user;
	mwProject m_active_project;
	std::map<int, mwTask> m_seen_tasks;
	bool m_is_project_selected;
};

