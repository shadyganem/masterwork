#include "view/NewProjectFrame.h"

mw::NewProjectFrame::NewProjectFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* m_top_sizer;
	m_top_sizer = new wxBoxSizer(wxVERTICAL);

	m_main_form = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* m_name_sizer;
	m_name_sizer = new wxBoxSizer(wxHORIZONTAL);

	m_project_name_static_name = new wxStaticText(m_main_form, wxID_ANY, wxT("Project Name"), wxDefaultPosition, wxDefaultSize, 0);
	m_project_name_static_name->Wrap(-1);
	m_name_sizer->Add(m_project_name_static_name, 0, wxALL, 5);

	m_project_name_textbox = new wxTextCtrl(m_main_form, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_name_sizer->Add(m_project_name_textbox, 1, wxALL, 5);

	bSizer23->Add(m_name_sizer, 1, wxEXPAND, 5);



	wxBoxSizer* m_buttons;
	m_buttons = new wxBoxSizer(wxHORIZONTAL);


	m_button2 = new wxButton(m_main_form, wxID_ANY, wxT("Done"), wxDefaultPosition, wxDefaultSize, 0);
	m_buttons->Add(m_button2, 0, wxALL, 5);


	m_cancel_button = new wxButton(m_main_form, wxID_ANY, wxT("Done"), wxDefaultPosition, wxDefaultSize, 0);
	m_buttons->Add(m_cancel_button, 0, wxALL, 5);

	bSizer23->Add(m_buttons, 0, wxALIGN_RIGHT, 5);

	m_main_form->SetSizer(bSizer23);
	m_main_form->Layout();
	bSizer23->Fit(m_main_form);
	m_top_sizer->Add(m_main_form, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(m_top_sizer);
	this->Layout();

	// Connect Events
	m_button2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewProjectFrame::OnDoneButton), NULL, this);
	m_cancel_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewProjectFrame::OnCancelButton), NULL, this);

}

mw::NewProjectFrame::~NewProjectFrame()
{
	// Disconnect Events
	m_button2->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewProjectFrame::OnDoneButton), NULL, this);
	m_cancel_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(NewProjectFrame::OnCancelButton), NULL, this);

}

void mw::NewProjectFrame::SetProject(mwProject& project)
{
	m_project = project;
	m_project_name_textbox->SetLabel(m_project.name);
}

void mw::NewProjectFrame::OnDoneButton(wxCommandEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	
	m_project.name = this->m_project_name_textbox->GetLineText(0).ToStdString();
	if (m_project.name == "")
	{
		this->Close();
		return;
	}
	controller.AddProject(m_project);
	this->Close();
}

void mw::NewProjectFrame::OnCancelButton(wxCommandEvent& event)
{
	this->Close();
}
