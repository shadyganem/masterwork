#include "view/PasswordFrame.h"

mw::PasswordFrame::PasswordFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) 
	: wxFrame(parent, id, title, pos, size, style)
{
    // Create main sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Create username field
    wxStaticText* usernameLabel = new wxStaticText(this, wxID_ANY, wxT("Username:"));
    username_textctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
    mainSizer->Add(usernameLabel, 0, wxALL | wxEXPAND, 10);
    mainSizer->Add(username_textctrl, 0, wxALL | wxEXPAND, 10);

    // Create password field
    wxStaticText* passwordLabel = new wxStaticText(this, wxID_ANY, wxT("Password:"));
    password_textctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    mainSizer->Add(passwordLabel, 0, wxALL | wxEXPAND, 10);
    mainSizer->Add(password_textctrl, 0, wxALL | wxEXPAND, 10);

    // Create URL field
    wxStaticText* urlLabel = new wxStaticText(this, wxID_ANY, wxT("URL:"));
    url_textctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
    mainSizer->Add(urlLabel, 0, wxALL | wxEXPAND, 10);
    mainSizer->Add(url_textctrl, 0, wxALL | wxEXPAND, 10);

    // Create notes field
    wxStaticText* notesLabel = new wxStaticText(this, wxID_ANY, wxT("Notes:"));
    notes_textctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    mainSizer->Add(notesLabel, 0, wxALL | wxEXPAND, 10);
    mainSizer->Add(notes_textctrl, 1, wxALL | wxEXPAND, 10);

    // Create Add button
    wxButton* addButton = new wxButton(this, wxID_ANY, wxT("Add"));
    addButton->Bind(wxEVT_BUTTON, &PasswordFrame::OnAddButtonClicked, this);
    mainSizer->Add(addButton, 0, wxALL | wxALIGN_CENTER, 10);

    // Set the main sizer for the frame
    SetSizerAndFit(mainSizer);
}

mw::PasswordFrame::~PasswordFrame()
{
}

void mw::PasswordFrame::SetPassword(mw::Password password)
{
    this->m_password = password;
    this->SetTitle(this->m_password.username);
    username_textctrl->SetValue(m_password.username);
    password_textctrl->SetValue(m_password.encrypted_password);
    url_textctrl->SetValue(m_password.url);
    notes_textctrl->SetValue(m_password.notes);
}

void mw::PasswordFrame::OnAddButtonClicked(wxCommandEvent& event)
{
    

    mw::Controller& controller = mw::Controller::Get();

    wxString username = username_textctrl->GetValue();
    wxString password = password_textctrl->GetValue();
    wxString url = url_textctrl->GetValue();
    wxString notes = notes_textctrl->GetValue();



    if (!password.empty()) 
    {
        this->m_password.StampCreationTime();
        this->m_password.password = password.ToStdString();
        // ToDo: the password needs to be stored with encryption
        this->m_password.encrypted_password = password.ToStdString();
        this->m_password.url = url.ToStdString();
        this->m_password.notes = notes.ToStdString();
        this->m_password.username = username.ToStdString();

        controller.AddPassword(m_password);
    }
    this->Close();
}
