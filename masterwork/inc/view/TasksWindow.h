#pragma once

#include "wx/wx.h"
#include "view/TaskPanel.h"
#include "controller/Controller.h"
#include "mwDefines.h"
#include "model/Task.h"
#include <map>
#include "view/Button.h"
#include<chrono>
#include <wx/notifmsg.h>
#include <wx/dataview.h>
#include "view/TaskFrame.h"
#include "mwDefines.h"

#define mwID_EDIT = 1

namespace mw
{
	class TasksWindow : public wxScrolledWindow
	{

	public:
		TasksWindow(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxScrolledWindowStyle, const wxString& name = wxASCII_STR(wxPanelNameStr));
		~TasksWindow();

		virtual void OnUpdateUI(wxEvent& event);
		virtual void OnNewTaskButton(wxCommandEvent& event);
		virtual void OnItemActivated(wxDataViewEvent& event);
		virtual void OnSelectionChanged(wxDataViewEvent& event);
		virtual void OnItemContextMenu(wxDataViewEvent& event);
		virtual void OnTaskEditClick(wxCommandEvent& event);
		virtual void OnTaskDeleteClick(wxCommandEvent& event);
		virtual void OnTaskArchieveClick(wxCommandEvent& event);
		virtual void AddTask(mw::Task& task);
		virtual void OnToolbarButtonClick(wxCommandEvent& event);
		virtual void OnNewTasksFrameCloseEvent(wxCloseEvent& event);
		virtual void OnProjectChanged(wxEvent& event);

	public:
		std::map<mw::Task, mw::TaskFrame*> m_task_to_frame_map;
		std::map<int, mw::Task> m_index_to_task_map;
		wxDataViewListCtrl* m_tasks_data_view_list;
		wxMenu* m_menu;
		wxButton* m_new_task_button;
		std::map<mw::TaskPanel*, mw::Task> m_taskpanel_to_task_map;
		std::map<mw::Task, mw::TaskPanel*> m_task_to_taskpanel_map;
		wxBoxSizer* m_tasks_sizer;

		mw::Project m_current_project;
		mw::TaskPanel* m_task_panel;
		wxToolBar* m_toolbar;

	private:
		void GetSelectedTasks(std::vector<mw::Task>& tasks);

	};
}
