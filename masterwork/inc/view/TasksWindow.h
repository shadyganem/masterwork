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

namespace mw
{
	class TasksWindow : public wxScrolledWindow
	{

	public:
		TasksWindow(wxWindow* parent,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxScrolledWindowStyle,
			const wxString& name = wxASCII_STR(wxPanelNameStr));
		~TasksWindow();

		virtual void OnUpdateUI(wxEvent& event);
		virtual void OnNewTaskButton(wxCommandEvent& event);
		virtual void OnTaskScrollWindowLeaveWindow(wxMouseEvent& event);
		virtual void OnItemActivated(wxDataViewEvent& event);
		virtual void AddTask(mw::Task& task);


	public:
		std::map<int, mw::Task> m_index_to_task_map;
		wxDataViewListCtrl* m_tasks_data_view_list;
		wxButton* m_new_task_button;
		std::map<mw::TaskPanel*, mw::Task> m_taskpanel_to_task_map;
		std::map<mw::Task, mw::TaskPanel*> m_task_to_taskpanel_map;
		wxBoxSizer* m_tasks_sizer;

	private:
		DECLARE_EVENT_TABLE()
	};
}
