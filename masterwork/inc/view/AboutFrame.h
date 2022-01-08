#pragma once

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include "controller/mwLogger.h"

namespace mw
{
class AboutFrame : public wxFrame
{

public:
	wxPanel* m_about_panel;
	wxStaticText* m_staticText26;
	wxButton* m_ok_button;

	// Virtual event handlers, overide them in your derived class
	virtual void OnOkClick(wxCommandEvent& event);
public:
	AboutFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("MasterWork About"), const wxPoint& pos = wxPoint(400, 200), const wxSize& size = wxSize(600, 200), long style = wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
	~AboutFrame();
};

}
