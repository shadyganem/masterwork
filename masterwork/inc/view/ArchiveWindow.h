#pragma once
#include "wx/wx.h"
#include "view/TaskPanel.h"
#include "controller/Controller.h"
#include "mwDefines.h"
#include "model/Task.h"
#include <map>

namespace mw
{
	class ArchiveWindow : public wxScrolledWindow
	{

	public:
		ArchiveWindow(wxWindow* parent,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxScrolledWindowStyle,
			const wxString& name = wxASCII_STR(wxPanelNameStr));

		~ArchiveWindow();

		virtual void OnUpdateUI(wxEvent& event);
		virtual void OnTaskScrollWindowLeaveWindow(wxMouseEvent& event);


	public:
		std::map<mw::TaskPanel*, mw::Task> m_taskpanel_to_task_map;
		std::map<mw::Task, mw::TaskPanel*> m_task_to_taskpanel_map;
		wxBoxSizer* m_tasks_sizer;

	private:
		DECLARE_EVENT_TABLE()
	};
}
