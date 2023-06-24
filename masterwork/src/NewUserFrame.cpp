#include "view/NewUserFrame.h"


mw::NewUserFrame::NewUserFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) 
	: wxFrame(parent, id, title, pos, size, style)
{
		// Create the main panel
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	// Create username label and text control
	m_username_text_ctrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	m_username_text_ctrl->SetHint("Username");

	// Create password label and text control
	
	m_password_text_ctrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD | wxTE_PROCESS_ENTER);
	m_password_text_ctrl->SetHint("Password");
	m_password_text_ctrl->SetEditable(false);

	// Create password confirmation label and text control
	m_confirm_text_ctrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD | wxTE_PROCESS_ENTER);
	m_confirm_text_ctrl->SetHint("Confirm Password");
	m_confirm_text_ctrl->SetEditable(false);

	// Create password protection checkbox
	m_password_protection_checkbox = new wxCheckBox(panel, wxID_ANY, "Enable Password Protection");
	m_password_protection_checkbox->SetValue(false);

	// Create OK button
	wxButton* okButton = new wxButton(panel, wxID_OK, "OK");

	// Create sizer for layout
	m_sizer = new wxBoxSizer(wxVERTICAL);
	m_sizer->Add(m_username_text_ctrl, 0, wxEXPAND | wxALL, 5);
	m_sizer->Add(m_password_protection_checkbox, 0, wxALL, 5);
	m_sizer->Add(m_password_text_ctrl, 0, wxEXPAND | wxALL, 5);
	m_sizer->Add(m_confirm_text_ctrl, 0, wxEXPAND | wxALL, 5);
	m_sizer->Add(okButton, 0, wxALIGN_CENTER | wxALL, 5);
	panel->SetSizerAndFit(m_sizer);

	this->Fit();
	// Bind events
	Bind(wxEVT_BUTTON, &NewUserFrame::OnOKButtonClicked, this, wxID_OK);
	Bind(wxEVT_TEXT_ENTER, &NewUserFrame::OnOKButtonClicked, this, wxID_ANY);
	Bind(wxEVT_CHECKBOX, &NewUserFrame::OnCheckBoxChanged, this, m_password_protection_checkbox->GetId());
}

mw::NewUserFrame::~NewUserFrame()
{
}

void mw::NewUserFrame::OnOKButtonClicked(wxCommandEvent& event)
{
	wxString username = m_username_text_ctrl->GetValue();
	wxString password = m_password_text_ctrl->GetValue();
	wxString confirm = m_confirm_text_ctrl->GetValue();

	if (password != confirm) {
		wxMessageBox("Passwords do not match. Please try again.", "Error", wxOK | wxICON_ERROR);
		m_password_text_ctrl->SetValue("");
		m_confirm_text_ctrl->SetValue("");
		m_password_text_ctrl->SetFocus();
		return;
	}

	// Process the username and password as needed (e.g., create a new user)

	mw::Controller& controller = mw::Controller::Get();
	mw::User user;

	user.username = username.ToStdString();
	if (user.username == "")
	{
		this->Close();
		return;
	}
	user.is_password_protected = m_password_protection_checkbox->GetValue();
	if (user.is_password_protected)
	{
		user.SetPassword(password.ToStdString());
	}

	controller.AddUser(user);

	Close();
}

void mw::NewUserFrame::OnCheckBoxChanged(wxCommandEvent& event)
{
	if (m_password_protection_checkbox->GetValue())
	{
		m_password_text_ctrl->SetEditable(true);
		m_confirm_text_ctrl->SetEditable(true);
	}
	else
	{
		m_password_text_ctrl->SetEditable(false);
		m_confirm_text_ctrl->SetEditable(false);
	}
}
