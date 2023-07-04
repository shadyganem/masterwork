#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <string>
#include "controller/Controller.h"
#include "model/Password.h"

namespace mw
{
    class NewPasswordFrame : public wxFrame
    {

    public:
        NewPasswordFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Password"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(450, 400), long style = wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT | wxTAB_TRAVERSAL);
        ~NewPasswordFrame();
    private:
        virtual void OnAddButtonClicked(wxCommandEvent& event);
    private:

        wxTextCtrl* username_textctrl;
        wxTextCtrl* password_textctrl;
        wxTextCtrl* url_textctrl;
        wxTextCtrl* notes_textctrl;
        mw::Password m_password;
    };
}


