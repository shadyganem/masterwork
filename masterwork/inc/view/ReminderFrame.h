#pragma once

#include <wx/frame.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include "model/Reminder.h"
#include "wx/wx.h"
#include "controller/Controller.h"
#include <wx/clrpicker.h>


namespace mw
{
	class ReminderFrame : public wxFrame
	{

	public:
		ReminderFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Reminder"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(450, 400), long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
		~ReminderFrame();
		
		void SetReminder(const mw::Reminder& reminder);
	private:
		void OnSaveButton(wxCommandEvent& event);
		mw::Reminder m_reminder;
		// Member variables for the form components
		wxTextCtrl* title_input;
		wxTextCtrl* text_input;
		wxButton* save_button;
		bool m_new_reminder;
		wxChoice* m_repeat_options;
		wxCheckListBox* m_alert_options_checklist_box;
		wxColourPickerCtrl* m_color_picker;
	};
}

