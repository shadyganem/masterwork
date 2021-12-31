#pragma once

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/frame.h>

#include "controller/mwController.h"
#include "model/mwProject.h"
#include <string>


class mwNewProjectFrame : public wxFrame
{
private:
	mwProject m_project;
protected:
	wxPanel* m_main_form;
	wxStaticText* m_project_name_static_name;
	wxTextCtrl* m_project_name_textbox;
	wxButton* m_button2;

	// Virtual event handlers, overide them in your derived class
	virtual void OnDoneButton(wxCommandEvent& event);


public:
	mwNewProjectFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New Project"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 176), long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
	~mwNewProjectFrame();
	void SetProject(mwProject& project);

};