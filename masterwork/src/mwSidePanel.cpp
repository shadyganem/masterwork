#include "view/mwSidePanel.h"


BEGIN_EVENT_TABLE(mwSidePanel, wxPanel)
	EVT_CUSTOM(mwUpdateUI, SIDE_PANEL_ID, mwSidePanel::OnUpdateUI)
END_EVENT_TABLE()


void mwSidePanel::UpdateProjecstList()
{
	mwLogger logger;

	
	m_projects_list->Clear();

	mwController& controller = mwController::Get();
	std::vector<mwProject> projects;
	controller.GetProjectsForActiveUser(projects);
	wxString project_name;
	for (int i = 0; i < projects.size(); i++)
	{
		m_place_to_project_map[i] = projects[i];
		project_name = projects[i].name;
		logger.Info(project_name.ToStdString());
		m_projects_list->InsertItems(1, &project_name, i);
	}
}

void mwSidePanel::OnUpdateUI(wxEvent& event)
{
	mwLogger logger;
	logger.Info("updating side panel");
	this->UpdateProjecstList();
	this->Layout();
}

void mwSidePanel::OnItemSelect(wxCommandEvent& event)
{
	mwLogger logger;
	mwController& controller = mwController::Get();
	int sel_item;
	sel_item = this->m_projects_list->GetSelection();
	logger.Info(std::to_string(sel_item));
	controller.SetActiveProject(m_place_to_project_map[sel_item]);
}

mwSidePanel::mwSidePanel(wxWindow* parent,
	                     wxWindowID winid, 
	                     const wxPoint& pos, 
	                     const wxSize& size, 
	                     long style, 
	                     const wxString& name) : wxPanel(parent, winid, pos, size, style, name)
{
	mwController& controller = mwController::Get();
	controller.RegisterEventHandler(SIDE_PANEL_ID, this);
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer(wxVERTICAL);

	m_splitter1 = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D);
	m_splitter1->Connect(wxEVT_IDLE, wxIdleEventHandler(mwSidePanel::m_splitter1OnIdle), NULL, this);
	m_panel7 = new wxPanel(m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer(wxVERTICAL);

	m_projects_text = new wxStaticText(m_panel7, wxID_ANY, wxT("Projects"), wxDefaultPosition, wxDefaultSize, 0);
	m_projects_text->Wrap(-1);
	m_projects_text->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));

	bSizer21->Add(m_projects_text, 0, wxALL | wxEXPAND, 5);

	m_projects_list = new wxListBox(m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	bSizer21->Add(m_projects_list, 1, wxALL | wxEXPAND, 5);

	m_panel7->SetSizer(bSizer21);
	m_panel7->Layout();
	bSizer21->Fit(m_panel7);
	m_panel9 = new wxPanel(m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer(wxVERTICAL);

	m_panel9->SetSizer(bSizer22);
	m_panel9->Layout();
	bSizer22->Fit(m_panel9);
	m_splitter1->SplitHorizontally(m_panel7, m_panel9, 324);
	bSizer19->Add(m_splitter1, 1, wxEXPAND, 5);

	this->SetSizer(bSizer19);
	this->Layout();
	this->UpdateProjecstList();

	m_projects_list->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(mwSidePanel::OnItemSelect), NULL, this);
}

mwSidePanel::~mwSidePanel()
{
	m_projects_list->Disconnect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(mwSidePanel::OnItemSelect), NULL, this);
}
