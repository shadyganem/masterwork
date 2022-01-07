#include "view/AboutFrame.h"

mw::AboutFrame::AboutFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
{

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* m_main_siizer;
	m_main_siizer = new wxBoxSizer(wxVERTICAL);

	m_about_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer53;
	bSizer53 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer(wxVERTICAL);

	m_staticText26 = new wxStaticText(m_about_panel, wxID_ANY, wxT("MasterWork® Version 1.0.0\n\nMasterWork® all right reserved.\nThis computer program is protected by copyright law and international treaties. "), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText26->Wrap(-1);
	bSizer55->Add(m_staticText26, 1, wxALL | wxEXPAND, 5);

	bSizer53->Add(bSizer55, 1, wxEXPAND, 5);

	m_buttons = new wxStdDialogButtonSizer();
	m_buttonsOK = new wxButton(m_about_panel, wxID_OK);
	m_buttons->AddButton(m_buttonsOK);
	m_buttons->Realize();
	bSizer53->Add(m_buttons, 0, wxALL | wxEXPAND, 5);

	m_about_panel->SetSizer(bSizer53);
	m_about_panel->Layout();
	bSizer53->Fit(m_about_panel);
	m_main_siizer->Add(m_about_panel, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(m_main_siizer);
	this->Layout();

	// Connect Events
	m_buttonsOK->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AboutFrame::OnOkClick), NULL, this);

}
mw::AboutFrame::~AboutFrame()
{
	// Disconnect Events
	m_buttonsOK->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AboutFrame::OnOkClick), NULL, this);
}
