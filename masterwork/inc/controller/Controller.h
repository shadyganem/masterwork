#pragma once

#include "wx/wx.h"
#include <wx/thread.h>
#include <wx/event.h>
#include "mwDefines.h"
#include "model/Model.h"
#include "model/Task.h"
#include "model/User.h"
#include "controller/Logger.h"
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
			static mw::Controller instance;
			return instance;
		}
		// mwController interface
		void Init();
		bool Search(wxString& search_query);
		wxString GetActiveUsername(void);
		void GetActiveProject(mwProject& project);
		void SetActiveUser(int user_uid);
		void SetActiveUser(mw::User& user);
		void SetActiveProject(mwProject& project);
		void SetStatusBarText(const wxString& txt);
		wxString GetStatusBarText(void);
		void SetInfoBarText(const wxString& txt);
		wxString GetInfoBarText(void);
		void RegisterMainFrame(wxEvtHandler* mf);
		void RegisterEventHandler(int ID, wxEvtHandler* event_handler);
		void AddTask(std::string name, std::string dec);
		void DeleteTask(Task& task);
		void UnArchiveTask(Task& task);
		void DeleteProject(mwProject& project);
		void AddTask(Task& task);
		void AddProject(mwProject& project);
		void AddUser(mw::User& user, bool set_active=false);
		void GetAllUsers(std::vector<mw::User>& users);
		void GetProjectsForActiveUser(std::vector<std::string>& projects);
		void GetProjectsForActiveUser(std::vector<mwProject>& projects);
		void GetTasksForActiveProject(std::vector<Task>& tasks);
		void GetArchiveTasksForActiveProject(std::vector<Task>& tasks);
		void RequestUpdateUI(int wind_id);
		void SetActiveWindow(int winid);

	private:
		Controller() {}
		void PostUpdateUI(int windId);
		void PostNotification(int windId);
		wxEvtHandler* m_main_frame;
		wxVector <wxEvtHandler*> m_events_handlers;
		std::map<int, wxEvtHandler*> m_event_handlers;
		wxString m_status_bar_text;
		wxString m_info_bar_text;
		Model m_model;
		wxMutex m_mutex;
		mwProject m_current_project;
		Logger m_logger;
		User m_active_user;
		mwProject m_active_project;
		std::map<int, Task> m_seen_tasks;
		bool m_is_project_selected;
		int m_active_winid;
	};
}