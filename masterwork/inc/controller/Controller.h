#pragma once

#include "wx/wx.h"
#include <wx/thread.h>
#include <wx/event.h>
#include "mwDefines.h"
#include "model/Model.h"
#include "model/Task.h"
#include "model/User.h"
#include "model/Password.h"
#include "controller/Logger.h"
#include <vector>
#include <map>
#include <thread>

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
		void GetActiveProject(Project& project);
		void SetActiveUser(int user_uid);
		void SetActiveUser(mw::User& user, bool post_update_ui = true);
		void SetActiveProject(Project& project, bool post_update_ui = true);
		void SetStatusBarText(const wxString& txt);
		void SetStatusBar(const wxString& txt,const wxColour& color);
		wxString GetStatusBarText(void);
		void SetStatusBarColour(wxColour colour);
		wxColour GetStatusBarColour(void);
		void SetInfoBarText(const wxString& txt);
		wxString GetInfoBarText(void);
		void RegisterMainFrame(wxEvtHandler* mf);
		void RegisterEventHandler(int ID, wxEvtHandler* event_handler);
		void DeleteTask(Task& task);
		void DeleteTasks(std::vector<mw::Task>& tasks);
		void DeleteReminders(std::vector<mw::Reminder>& reminders);
		void DeletePasswords(std::vector<mw::Password>& passwords);
;		void ArchiveTask(Task& task);
		void ArchiveTasks(std::vector<mw::Task>& tasks);
		void UnarchiveTask(Task& task);
		void UnarchiveTasks(std::vector<mw::Task>& tasks);
		void DeleteProject(Project& project);
		void AddTask(Task& task);
		void AddProject(Project& project, bool post_update_ui = true);
		void AddUser(mw::User& user, bool set_active=false, bool post_update_ui = true);
		void AddReminder(mw::Reminder& reminder, bool post_update_ui = true);
		void AddPassword(mw::Password& password, bool post_update_ui = true);
		void UpdateRreminder(mw::Reminder& reminder, bool post_update_ui = true);
		void GetAllUsers(std::vector<mw::User>& users);
		void GetProjectsForActiveUser(std::vector<std::string>& projects);
		void GetProjectsForActiveUser(std::vector<Project>& projects);
		void GetRemindersForActiveUser(std::vector<mw::Reminder>& reminders);
		void GetTasksForActiveProject(std::vector<Task>& tasks);
		void GetPasswordsForActiveUser(std::vector<mw::Password>& passwords);
		void GetArchiveTasksForActiveProject(std::vector<Task>& tasks);
		void RequestUpdateUI(int wind_id=-2);
		void SetActiveWindow(int winid);

	private:
		Controller() {}
		void PostUpdateUI(int windId);
		void PostProjectChangedEevent(int winID);
		void PostNotification(int windId);
		wxEvtHandler* m_main_frame;
		wxVector <wxEvtHandler*> m_events_handlers;
		std::map<int, wxEvtHandler*> m_event_handlers;
		wxString m_status_bar_text;
		wxColour m_status_bar_colour;
		wxString m_info_bar_text;
		Model m_model;
		wxMutex m_mutex;
		Project m_current_project;
		Logger m_logger;
		User m_active_user;
		Project m_active_project;
		std::map<int, Task> m_seen_tasks;
		bool m_is_project_selected;
		int m_active_winid;
	public:
		wxColour m_backgroud_color;
		wxColour m_foreground_color;
	};
}