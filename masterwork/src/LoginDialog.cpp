#include "view/LoginDialog.h"

mw::LoginDialog::LoginDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(nullptr, MAIN_FRAME_ID, title, pos, size)
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
    login_button->Bind(wxEVT_BUTTON, &mw::LoginDialog::OnLogin, this);

    vbox->Add(login_button, 0, wxALIGN_CENTER | wxALL, 5);

    panel->SetSizer(vbox);
    Centre();
    this->Fit();
}

mw::LoginDialog::~LoginDialog()
{
}

void mw::LoginDialog::OnLogin(wxCommandEvent& event)
{
    wxString username = m_username_text_ctrl->GetValue();
    wxString password = m_password_text_ctrl->GetValue();
    mw::PasswordHasher hasher;
    mw::Logger logger;
    logger.EnableDebug();
    logger.Debug(m_user.hashed_password);
    logger.DisableDebug();
    m_login_status = hasher.verifyPassword(password.ToStdString(), m_user.hashed_password);
    if (m_login_status)
    {
        this->EndModal(wxID_OK);
    }
    else
    {
        this->EndModal(wxID_ABORT);
    }
}

bool mw::LoginDialog::GetLoginStatus()
{
    return m_login_status;
}

void mw::LoginDialog::SetUser(mw::User& user)
{
    m_username_text_ctrl->SetValue(user.username);
    m_username_text_ctrl->Disable();
    m_user = user;
}


