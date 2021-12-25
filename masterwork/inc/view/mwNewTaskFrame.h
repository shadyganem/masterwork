#pragma once

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/frame.h>

#include "controller/mwLogger.h"
#include "controller/mwController.h"
#include "model/mwTask.h"


class mwNewTaskFrame : public wxFrame
{
private:

protected:
	wxPanel* m_main_panel;
	wxStaticText* m_task_name_static;
	wxTextCtrl* m_task_name;
	wxStaticText* m_task_description_static;
	wxTextCtrl* m_task_description;
	wxStaticText* m_priority_static;
	wxChoice* m_priority_choice;
	wxStaticText* m_status_static;
	wxChoice* m_status_choice;
	wxStaticText* m_deadline_static;
	wxSpinCtrl* m_hour_spin;
	wxSpinCtrl* m_spinCtrl6;
	wxDatePickerCtrl* m_datePicker2;
	wxButton* m_done_button;
	wxButton* m_cancel_button;

	// Virtual event handlers, overide them in your derived class
	virtual void OnDoneButton(wxCommandEvent& event);
	virtual void OnCancelButton(wxCommandEvent& event);


public:
	mwNewTaskFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New Task"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(458, 422), long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
	~mwNewTaskFrame();

};

