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
#include "controller/NotificationFactory.h"
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
		wxString GetStatusBarText(void);
		void SetInfoBarText(const wxString& txt);
		wxString GetInfoBarText(void);
		void RegisterMainFrame(wxEvtHandler* mf);
		void RegisterEventHandler(int ID, wxEvtHandler* event_handler);
		void DeleteTask(Task& task);
		void ArchiveTask(Task& task);
		void UnArchiveTask(Task& task);
		void DeleteProject(Project& project);
		void AddTask(Task& task);
		void AddProject(Project& project, bool post_update_ui = true);
		void AddNotification(mw::Notification& notification, bool post_update_ui = true);
		void AddUser(mw::User& user, bool set_active=false, bool post_update_ui = true);
		void AddReminder(mw::Reminder& reminder, bool post_update_ui = true);
		void UpdateNotification(mw::Notification& notification, bool post_update_ui = true);
		void GetAllUsers(std::vector<mw::User>& users);
		void GetProjectsForActiveUser(std::vector<std::string>& projects);
		void GetProjectsForActiveUser(std::vector<Project>& projects);
		void GetNotificationsForActiveUser(std::vector<mw::Notification>& notifications);
		void GetRemindersForActiveUser(std::vector<mw::Reminder>& reminders);
		void GetTasksForActiveProject(std::vector<Task>& tasks);
		void GetArchiveTasksForActiveProject(std::vector<Task>& tasks);
		void RequestUpdateUI(int wind_id=-2);
		void SetActiveWindow(int winid);
		int GetNumOfNotifications(int& num, bool poll=true);
		void UpdateNotifications();

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
		Project m_current_project;
		Logger m_logger;
		User m_active_user;
		Project m_active_project;
		std::map<int, Task> m_seen_tasks;
		bool m_is_project_selected;
		int m_active_winid;
		int m_num_of_notifications;
	public:
		wxColour m_backgroud_color;
	};
}