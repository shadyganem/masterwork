#pragma once
#include "wx\scrolwin.h"
#include "controller/Controller.h"
#include "wx/wx.h"
#include "mwDefines.h"

namespace mw
{
	class RemindersWindow : public wxScrolledWindow
	{
	public:
		RemindersWindow(wxWindow* parent,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxScrolledWindowStyle,
			const wxString& name = wxASCII_STR(wxPanelNameStr));

		~RemindersWindow();

		virtual void OnUpdateUI(wxEvent& event);
		virtual void OnTaskScrollWindowLeaveWindow(wxMouseEvent& event);
	private:
		wxBoxSizer* m_tasks_sizer;
	};

}