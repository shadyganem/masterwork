#include "view/LoginDialog.h"

mw::LoginDialog::LoginDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(nullptr, MAIN_FRAME_ID, title, pos, size)
{
    m_login_status = false;
    // Create the login form elements
    this->SetSize(wxSize(400, 200));
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
    m_password_text_ctrl->Bind(wxEVT_KEY_UP, &mw::LoginDialog::OnKeyPress, this);

    vbox->Add(login_button, 0, wxALIGN_CENTER | wxALL, 5);

    panel->SetSizer(vbox);
    this->Centre();
}

mw::LoginDialog::~LoginDialog()
{
}

void mw::LoginDialog::OnLogin(wxCommandEvent& event)
{
    wxString username = m_username_text_ctrl->GetValue();
    wxString password = m_password_text_ctrl->GetValue();
    mw::PasswordHasher hasher;
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

void mw::LoginDialog::OnKeyPress(wxKeyEvent& event)
{
    if (event.GetKeyCode() == WXK_RETURN || event.GetKeyCode() == WXK_NUMPAD_ENTER) {
        // Check if the focus is on the password text control
        if (wxWindow::FindFocus() == m_password_text_ctrl)
        {
            wxCommandEvent loginEvent(wxEVT_COMMAND_BUTTON_CLICKED, wxID_OK);

            // Trigger the same logic as the login button click
            this->OnLogin(loginEvent);
            return;  // Exit early to prevent further processing
        }
    }

    // Allow the event to propagate for other key presses
    event.Skip();
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


