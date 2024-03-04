#pragma once

#include <wx/frame.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include "model/Reminder.h"
#include "wx/wx.h"
#include "controller/Controller.h"
#include <wx/clrpicker.h>
#include "view/Button.h"
#include <wx/datectrl.h>
#include "view/TimePicker.h"
#include "model/TimeOfDay.h"
#include <wx/timectrl.h>



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
		void OnCancelButton(wxCommandEvent& event);
		void OnRepeatOptionsChange(wxCommandEvent& event);
		void OnAlertTimingOptionChanged(wxCommandEvent& event);
		void HideAllRepeatOptions();
		void GetSelectedDaysOfTheWeek(std::vector<std::string> &selecteds_days);
		void GetSelectedAlertTimingOptions(std::vector<std::string> &selected);
		mw::Reminder m_reminder;
		// Member variables for the form components
		wxTextCtrl* title_input;
		wxTextCtrl* text_input;
		mw::Button* m_save_button;
		mw::Button* m_cancel_button;
		bool m_new_reminder;
		wxChoice* m_repeat_options;
		wxCheckListBox* m_alert_timing_checklist_box;
		wxCheckListBox* m_days_of_the_week;
		wxColourPickerCtrl* m_color_picker;
		wxStaticBoxSizer* m_options_box;
		wxBoxSizer* m_v_sizer;
		wxTimePickerCtrl* m_alert_timepicker;
		wxDatePickerCtrl* m_alert_datepicker;
		wxComboBox* m_day_dropdown;
		wxBoxSizer* m_main_sizer;
	};
}


