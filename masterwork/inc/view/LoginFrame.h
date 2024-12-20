#pragma once
#include "wx/wx.h"


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
#include "model/PasswordHasher.h"


namespace mw
{
	class LoginFrame : public wxFrame
	{
	public:
		LoginFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Login"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(450, 400), long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
		~LoginFrame();
		bool GetLoginStatus();

	private:
		virtual void OnUserChange(wxCommandEvent& event);
		void OnKeyPress(wxKeyEvent& event);
		wxStaticText* m_error_text;
		void UpdateUsersList();
		std::map<int, mw::User> m_idx_to_user;
		void OnLogin(wxCommandEvent& event);
		void OnTimerEvent(wxTimerEvent& event);
		wxChoice* m_users_choice;
		bool m_login_status;
		wxTextCtrl* m_password_text_ctrl;
		mw::User m_user;
		wxBoxSizer* m_vbox;
		wxTimer* m_timer;
	};
}
