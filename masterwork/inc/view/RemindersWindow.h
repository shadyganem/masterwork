#pragma once
#include "wx\scrolwin.h"
#include "controller/Controller.h"
#include "wx/wx.h"
#include "mwDefines.h"
#include <wx/listctrl.h>
#include "model/Reminder.h"

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
		virtual void AddRemider(mw::Reminder& remider);

	private:
		wxBoxSizer* m_reminders_sizer;
		wxListView* m_remiders_list_view;
		std::map<std::string, int> m_column_to_index_map;
	private:
		DECLARE_EVENT_TABLE()
	};

}