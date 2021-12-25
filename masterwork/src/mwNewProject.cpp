#include "view/mwNewProject.h"

mwNewProjectFrame::mwNewProjectFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
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

	m_button2 = new wxButton(m_main_form, wxID_ANY, wxT("Done"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer23->Add(m_button2, 0, wxALL | wxEXPAND, 5);

	m_main_form->SetSizer(bSizer23);
	m_main_form->Layout();
	bSizer23->Fit(m_main_form);
	m_top_sizer->Add(m_main_form, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(m_top_sizer);
	this->Layout();

	// Connect Events
	m_button2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwNewProjectFrame::OnDoneButton), NULL, this);
}

mwNewProjectFrame::~mwNewProjectFrame()
{
	// Disconnect Events
	m_button2->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mwNewProjectFrame::OnDoneButton), NULL, this);
}

void mwNewProjectFrame::OnDoneButton(wxCommandEvent& event)
{
	mwController& controller = mwController::Get();
	mwProject new_project;
	new_project.name = this->m_project_name_textbox->GetLineText(0).ToStdString();
	if (new_project.name == "")
	{
		this->Close();
		return;
	}
	controller.AddProject(new_project);
	this->Close();
}