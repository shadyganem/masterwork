#pragma once
#include "wx\scrolwin.h"
#include "controller/Controller.h"
#include "wx/wx.h"
#include "mwDefines.h"
#include <wx/listctrl.h>
#include "model/Reminder.h"
#include <wx/dataview.h>
#include "view/Button.h"
#include "view/NewReminderFrame.h"

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
		virtual void AddRemider(mw::Reminder& remider);
		virtual void OnNewReminderButton(wxCommandEvent& event);
	public:

		std::map<int, mw::Reminder> m_index_to_reminder_map;
		wxDataViewListCtrl* m_reminders_data_view_list;
	private:
		mw::Button* m_new_reminder_button;
		wxBoxSizer* m_reminders_sizer;
		std::map<std::string, int> m_column_to_index_map;
	private:
		DECLARE_EVENT_TABLE()
	};

}