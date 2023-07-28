#pragma once

#include <wx/frame.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include "model/Reminder.h"
#include "wx/wx.h"

namespace mw
{
	class NewReminderFrame : public wxFrame
	{

	public:
		NewReminderFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Reminder"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(450, 400), long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
		~NewReminderFrame();
		
		void SetReminder(const mw::Reminder& reminder);
	private:
		void OnSaveButton(wxCommandEvent& event);
		mw::Reminder m_reminder;
		// Member variables for the form components
		wxTextCtrl* titleInput;
		wxTextCtrl* textInput;
		wxButton* save_button;

	};
}


