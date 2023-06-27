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
#include "model/PasswordHasher.h"

namespace mw
{
    class LoginDialog : public wxDialog
    {
    public:
        LoginDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Login"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(450, 400), long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
        ~LoginDialog();
        virtual void OnLogin(wxCommandEvent& event);
        virtual bool GetLoginStatus();
        virtual void SetUser(mw::User& user);

    private:
        bool m_login_status;
        wxTextCtrl* m_username_text_ctrl;
        wxTextCtrl* m_password_text_ctrl;
        mw::User m_user;
    };
}

