#include "view/LoginFrame.h"

mw::LoginFrame::LoginFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
    this->SetSize(wxSize(400, 200));

    wxPanel* panel = new wxPanel(this);
    m_vbox = new wxBoxSizer(wxVERTICAL);

    m_username_text_ctrl = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    m_username_text_ctrl->SetHint("Username");
    m_username_text_ctrl->Hide();

    wxArrayString m_usernames;
    m_users_choice = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_usernames, 0);
    m_users_choice->SetSelection(0);
    

    m_password_text_ctrl = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    m_password_text_ctrl->SetHint("Password");

    wxString errorMessage = wxT("Incorrect password. Please try again.");
    m_error_text = new wxStaticText(panel, wxID_ANY, errorMessage, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
    m_error_text->SetForegroundColour(*wxRED);
    m_error_text->Hide();

    m_vbox->Add(m_users_choice, 0, wxEXPAND | wxALL, 5);
    m_vbox->Add(m_password_text_ctrl, 0, wxEXPAND | wxALL, 5);
    

    wxButton* login_button = new wxButton(panel, wxID_ANY, wxT("Login"));
    

    m_vbox->Add(login_button, 0, wxALIGN_CENTER | wxALL, 5);
    m_vbox->Add(m_error_text, 0, wxEXPAND | wxALL, 5);
    

    m_vbox->Layout();
    panel->SetSizer(m_vbox);
    this->Centre();

    m_timer = new wxTimer(this, wxID_ANY);
    this->UpdateUsersList();
    m_users_choice->Bind(wxEVT_COMMAND_CHOICE_SELECTED, &mw::LoginFrame::OnUserChange, this);
    login_button->Bind(wxEVT_BUTTON, &mw::LoginFrame::OnLogin, this);
    m_password_text_ctrl->Bind(wxEVT_KEY_UP, &mw::LoginFrame::OnKeyPress, this);
    this->Bind(wxEVT_TIMER, &mw::LoginFrame::OnTimerEvent, this, m_timer->GetId());
}

mw::LoginFrame::~LoginFrame()
{
}

void mw::LoginFrame::OnLogin(wxCommandEvent& event)
{
    mw::Controller& controller = mw::Controller::Get();
    wxString password = m_password_text_ctrl->GetValue();
    mw::PasswordHasher hasher;
    m_login_status = hasher.verifyPassword(password.ToStdString(), m_user.hashed_password);

    if (m_login_status)
    {
        controller.SetActiveUser(m_user);
        // Send a custom event to indicate successful login
        wxCommandEvent loginEvent(wxEVT_COMMAND_BUTTON_CLICKED, wxID_OK);
        wxPostEvent(this, loginEvent);
        // Close the login frame
        this->Close();
    }
    else
    {
        // Display an error message in the frame
        m_error_text->Show();
        m_timer->StartOnce(3000);  // 3000 milliseconds (3 seconds)
        // You might also choose to clear the password field for security reasons
        m_password_text_ctrl->Clear();
        // Refresh the layout to ensure the new static text is displayed
        m_vbox->Layout();
    }
}

void mw::LoginFrame::OnKeyPress(wxKeyEvent& event)
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

bool mw::LoginFrame::GetLoginStatus()
{
    return m_login_status;
}

void mw::LoginFrame::SetUser(mw::User& user)
{
    m_username_text_ctrl->SetValue(user.username);
    m_username_text_ctrl->Disable();
    m_user = user;
}

void mw::LoginFrame::OnUserChange(wxCommandEvent& event)
{
    int index = m_users_choice->GetSelection();
    m_user = m_idx_to_user[index];
    m_password_text_ctrl->Show(m_user.is_password_protected);
    m_vbox->Layout();
}

void mw::LoginFrame::UpdateUsersList()
{
    mw::Controller& controller = mw::Controller::Get();
    std::vector<mw::User> users;
    m_users_choice->Clear();
    controller.GetAllUsers(users);
    m_idx_to_user.clear();

    for (int i = 0; i < users.size(); i++)
    {
        m_users_choice->Append(users[i].username);
        m_idx_to_user[i] = users[i];
        if (users[i].is_active)
        {
            m_users_choice->SetSelection(i);
            m_user = users[i];
            m_password_text_ctrl->Show(m_user.is_password_protected);

        }
    }
}

void mw::LoginFrame::OnTimerEvent(wxTimerEvent& event)
{
    // Timer event occurred, disable the error message
    m_error_text->Hide();
    m_vbox->Layout();  // Refresh layout to reflect the change
}

