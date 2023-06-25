#include "view/LoginFrame.h"

mw::LoginFrame::LoginFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(nullptr, MAIN_FRAME_ID, title, pos, size)
{
    m_login_status = false;
    // Create the login form elements
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    m_username_text_ctrl = new wxTextCtrl(panel, wxID_ANY);
    m_username_text_ctrl->SetHint("Username");


    m_password_text_ctrl = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    m_password_text_ctrl->SetHint("Password");

    vbox->Add(m_username_text_ctrl, 0, wxEXPAND | wxALL, 5);
    vbox->Add(m_password_text_ctrl, 0, wxEXPAND | wxALL, 5);

    wxButton* login_button = new wxButton(panel, wxID_ANY, wxT("Login"));
    login_button->Bind(wxEVT_BUTTON, &mw::LoginFrame::OnLogin, this);

    vbox->Add(login_button, 0, wxALIGN_CENTER | wxALL, 5);

    panel->SetSizer(vbox);
    Centre();
    this->Fit();
}

mw::LoginFrame::~LoginFrame()
{
}

void mw::LoginFrame::OnLogin(wxCommandEvent& event)
{
    wxString username = m_username_text_ctrl->GetValue();
    wxString password = m_password_text_ctrl->GetValue();

    // Perform the login authentication logic here

    wxMessageBox(wxT("Logged in successfully!"), wxT("Login"), wxOK | wxICON_INFORMATION);   
}

bool mw::LoginFrame::GetLoginStatus()
{
    return m_login_status;
}


