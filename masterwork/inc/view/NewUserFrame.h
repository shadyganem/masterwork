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
#include "controller/Controller.h"
#include "model/User.h"

namespace mw
{
	class NewUserFrame : public wxFrame
	{
	private:

	protected:
		wxPanel* m_main_panel;
		wxStaticText* m_username_static;
		wxButton* m_done_button;
		wxButton* m_cancel_button;

		// Virtual event handlers, overide them in your derived class
		virtual void OnDoneButton(wxCommandEvent& event);
		virtual void OnCancelButton(wxCommandEvent& event);


	public:
		wxTextCtrl* m_username_text;
		NewUserFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New User"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 221), long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
		~NewUserFrame();

	};
}


