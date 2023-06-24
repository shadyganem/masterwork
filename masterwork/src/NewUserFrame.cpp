#include "view/NewUserFrame.h"

void mw::NewUserFrame::OnDoneButton(wxCommandEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();

	mw::User user;

	user.username = this->m_username_text->GetLineText(0).ToStdString();
	if (user.username == "")
	{
		this->Close();
		return;
	}
	controller.AddUser(user, true);
	this->Close();
}

void mw::NewUserFrame::OnCancelButton(wxCommandEvent& event)
{
	this->Close();
	event.Skip();
}

mw::NewUserFrame::NewUserFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* m_main_sizer;
	m_main_sizer = new wxBoxSizer(wxVERTICAL);

	m_main_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* m_sizer1;
	m_sizer1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* m_sizer2;
	m_sizer2 = new wxBoxSizer(wxVERTICAL);

	m_username_static = new wxStaticText(m_main_panel, wxID_ANY, wxT("Username"), wxDefaultPosition, wxDefaultSize, 0);
	m_username_static->Wrap(-1);
	m_sizer2->Add(m_username_static, 0, wxALL, 5);

	m_username_text = new wxTextCtrl(m_main_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_sizer2->Add(m_username_text, 0, wxALL | wxEXPAND, 5);

	m_sizer1->Add(m_sizer2, 5, wxEXPAND, 5);

	wxBoxSizer* m_sizer3;
	m_sizer3 = new wxBoxSizer(wxHORIZONTAL);

	m_done_button = new wxButton(m_main_panel, wxID_ANY, wxT("Done"), wxDefaultPosition, wxDefaultSize, 0);
	m_sizer3->Add(m_done_button, 0, wxALIGN_RIGHT | wxALL, 5);

	m_cancel_button = new wxButton(m_main_panel, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	m_sizer3->Add(m_cancel_button, 0, wxALL, 5);

	m_sizer1->Add(m_sizer3, 0, wxALIGN_BOTTOM | wxALIGN_RIGHT, 5);

	m_main_panel->SetSizer(m_sizer1);
	m_main_panel->Layout();
	m_sizer1->Fit(m_main_panel);
	m_main_sizer->Add(m_main_panel, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(m_main_sizer);
	this->Layout();

	// Connect Events
	m_done_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewUserFrame::OnDoneButton), NULL, this);
	m_cancel_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewUserFrame::OnCancelButton), NULL, this);
}

mw::NewUserFrame::~NewUserFrame()
{
	// Disconnect Events
	m_done_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewUserFrame::OnDoneButton), NULL, this);
	m_cancel_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewUserFrame::OnCancelButton), NULL, this);
}
