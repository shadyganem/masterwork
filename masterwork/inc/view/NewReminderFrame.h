#pragma once
#include <wx/frame.h>
#include "model/Reminder.h"

namespace mw
{
	class NewReminderFrame : public wxFrame
	{

	public:
		NewReminderFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Task"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(450, 400), long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
		~NewReminderFrame();

		void SetReminder(const mw::Reminder& reminder);
		mw::Reminder m_reminder;

	};
}


