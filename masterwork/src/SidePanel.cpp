#include "view/SidePanel.h"


BEGIN_EVENT_TABLE(mw::SidePanel, wxPanel)
	EVT_CUSTOM(mwUpdateUI, SIDE_PANEL_ID, mw::SidePanel::OnUpdateUI)
END_EVENT_TABLE()

static enum ProjectListPopupMenuItems
{
	Delete,
	Rename
};

void mw::SidePanel::UpdateProjecstList()
{
	mwLogger logger;
	m_projects_list->Clear();
	m_place_to_project_map.clear();
	mwController& controller = mwController::Get();
	std::vector<mwProject> projects;
	controller.GetProjectsForActiveUser(projects);
	wxString project_name;
	for (int i = 0; i < projects.size(); i++)
	{
		m_place_to_project_map[i] = projects[i];
		project_name = projects[i].name;
		m_projects_list->InsertItems(1, &project_name, i);
		if (projects[i].is_active == true)
		{
			m_projects_list->SetSelection(i);
		}
	}
}

void mw::SidePanel::OnUpdateUI(wxEvent& event)
{
	this->UpdateProjecstList();
	this->Layout();
}

void mw::SidePanel::OnItemSelect(wxCommandEvent& event)
{
	mwController& controller = mwController::Get();
	int sel_item = this->m_projects_list->GetSelection();
	controller.SetActiveProject(m_place_to_project_map[sel_item]);
}

void mw::SidePanel::OnProjectListRightUp(wxCommandEvent& event)
{
	const wxPoint pt = wxGetMousePosition();
	wxMenu menu;
	menu.Append(ProjectListPopupMenuItems::Rename, "Rename");
	menu.Append(ProjectListPopupMenuItems::Delete, "Delete");
	menu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(mw::SidePanel::OnProjectListMenuClick), NULL, this);
	m_projects_list->PopupMenu(&menu);
}

void mw::SidePanel::OnProjectListMenuClick(wxCommandEvent& evt)
{
	mwController& controller = mwController::Get();
	mwLogger logger;
	int sel_item;
	mwProject sel_proj;
	sel_item = this->m_projects_list->GetSelection();
	sel_proj = this->m_place_to_project_map[sel_item];
	mw::NewProjectFrame* new_project_form = new mw::NewProjectFrame(this);

	switch (evt.GetId()) 
	{
		case ProjectListPopupMenuItems::Rename:
			logger.Info("renaming " + sel_proj.name);
			new_project_form->SetProject(sel_proj);
			new_project_form->Show(true);
			break;
		case ProjectListPopupMenuItems::Delete:
			controller.DeleteProject(sel_proj);
			break;
	}
}

bool mw::SidePanel::IsProjectSelected()
{
	mwLogger logger;
	logger.EnableDebug();
	int sel_item;
	logger.Debug("this is a debug message");
	sel_item = this->m_projects_list->GetSelection();
	return false;
}

mw::SidePanel::SidePanel(wxWindow* parent,
	                     wxWindowID winid, 
	                     const wxPoint& pos, 
	                     const wxSize& size, 
	                     long style, 
	                     const wxString& name) : wxPanel(parent, winid, pos, size, style, name)
{
	mwController& controller = mwController::Get();
	controller.RegisterEventHandler(SIDE_PANEL_ID, this);
	m_is_project_seleted = false;
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer(wxVERTICAL);

	m_splitter1 = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D);
	m_splitter1->Connect(wxEVT_IDLE, wxIdleEventHandler(mw::SidePanel::m_splitter1OnIdle), NULL, this);
	m_panel7 = new wxPanel(m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer(wxVERTICAL);

	m_projects_text = new wxStaticText(m_panel7, wxID_ANY, wxT("Projects"), wxDefaultPosition, wxDefaultSize, 0);
	m_projects_text->Wrap(-1);
	m_projects_text->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));

	bSizer21->Add(m_projects_text, 0, wxALL | wxEXPAND, 5);

	m_projects_list = new wxListBox(m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_NEEDED_SB);
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

	m_projects_list->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(mw::SidePanel::OnItemSelect), NULL, this);
	m_projects_list->Connect(wxEVT_RIGHT_UP, wxCommandEventHandler(mw::SidePanel::OnProjectListRightUp), NULL, this);

}

mw::SidePanel::~SidePanel()
{
	m_projects_list->Disconnect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(mw::SidePanel::OnItemSelect), NULL, this);
	m_projects_list->Disconnect(wxEVT_RIGHT_UP, wxCommandEventHandler(mw::SidePanel::OnProjectListRightUp), NULL, this);
}
