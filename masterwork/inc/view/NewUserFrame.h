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
	public:
		wxPanel* m_main_panel;
		wxStaticText* m_username_static;
		wxButton* m_done_button;
		wxButton* m_cancel_button;

		wxTextCtrl* m_username_text;
		NewUserFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New User"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
		~NewUserFrame();

    private:
		wxBoxSizer* m_sizer;
		wxStaticText* m_username_label;
        wxTextCtrl* m_username_text_ctrl;
		wxStaticText* m_password_label;
        wxTextCtrl* m_password_text_ctrl;
        wxTextCtrl* m_confirm_text_ctrl;
		wxCheckBox* m_password_protection_checkbox;

        void OnOKButtonClicked(wxCommandEvent& event);
		void OnCheckBoxChanged(wxCommandEvent& event);
	};
}


