#include "view/SidePanel.h"


BEGIN_EVENT_TABLE(mw::SidePanel, wxPanel)
	EVT_CUSTOM(mwUpdateUI, SIDE_PANEL_ID, mw::SidePanel::OnUpdateUI)
END_EVENT_TABLE()

static enum ProjectListPopupMenuItems
{
	Delete,
	Rename
};

void mw::SidePanel::UpdateUsersList()
{
	mw::Controller& controller = mw::Controller::Get();
	std::vector<mw::User> users;
	m_users_choice->Clear();
	controller.GetAllUsers(users);
	wxArrayString m_usernames;
	m_idx_to_user.clear();
	for (int i = 0; i < users.size(); i++)
	{
		m_users_choice->Append(users[i].username);
		m_idx_to_user[i] = users[i];
		if (users[i].is_active == true)
		{
			m_users_choice->SetSelection(i);
		}
	}
}

void mw::SidePanel::UpdateProjecstList()
{
	mw::Logger logger;
	m_projects_list->Clear();
	m_place_to_project_map.clear();
	mw::Controller& controller = mw::Controller::Get();
	std::vector<mw::Project> projects;
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
	this->UpdateUsersList();
	this->UpdateProjecstList();
}

void mw::SidePanel::OnItemSelect(wxCommandEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
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

void mw::SidePanel::OnNewProjectButton(wxCommandEvent& event)
{
	mw::NewProjectFrame* new_project_form = new mw::NewProjectFrame(this);
	new_project_form->CenterOnScreen();
	new_project_form->Show(true);
	event.Skip();
}

void mw::SidePanel::OnProjectListMenuClick(wxCommandEvent& evt)
{
	mw::Controller& controller = mw::Controller::Get();
	int sel_item;
	mw::Project sel_proj;
	sel_item = this->m_projects_list->GetSelection();
	sel_proj = this->m_place_to_project_map[sel_item];
	mw::NewProjectFrame* new_project_form = new mw::NewProjectFrame(this);

	switch (evt.GetId()) 
	{
		case ProjectListPopupMenuItems::Rename:
			new_project_form->SetProject(sel_proj);
			new_project_form->CenterOnScreen();
			new_project_form->Show(true);
			break;
		case ProjectListPopupMenuItems::Delete:
			controller.DeleteProject(sel_proj);
			break;
	}
}

void mw::SidePanel::OnUserChange(wxCommandEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	int idx = m_users_choice->GetSelection();
	controller.SetActiveUser(m_idx_to_user[idx]);
}

bool mw::SidePanel::IsProjectSelected()
{
	int sel_item;
	sel_item = this->m_projects_list->GetSelection();
	return false;
}

mw::SidePanel::SidePanel(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, 
	                     const wxString& name) : wxPanel(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(SIDE_PANEL_ID, this);
	m_is_project_seleted = false;
	wxBoxSizer* bSizer19 = new wxBoxSizer(wxVERTICAL);

	m_splitter1 = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D);
	m_splitter1->Connect(wxEVT_IDLE, wxIdleEventHandler(mw::SidePanel::m_splitter1OnIdle), NULL, this);
	m_panel7 = new wxPanel(m_splitter1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer(wxVERTICAL);

	wxArrayString m_usernames;
	m_users_choice = new wxChoice(m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_usernames, 0);
	m_users_choice->SetSelection(0);

	bSizer21->Add(m_users_choice, 0, wxRIGHT | wxLEFT | wxTOP | wxEXPAND, 5);

	m_new_project_button = new mw::Button(m_panel7, TOP_PANEL_NEW_TASK_ID, "New Project", wxDefaultPosition, wxDefaultSize);
	m_new_project_button->SetMinSize(wxSize(-1, 20));
	wxColour buttons_green(0, 136, 135);
	wxColour dark_panel(37, 37, 38);
	m_panel7->SetBackgroundColour(dark_panel);
	m_new_project_button->SetBackgroundColour(dark_panel);
	m_new_project_button->SetForegroundColour(buttons_green);
	bSizer21->Add(m_new_project_button, 0, wxALIGN_CENTER_HORIZONTAL | wxALL , 5);


	m_projects_list = new wxListBox(m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_NEEDED_SB);
	bSizer21->Add(m_projects_list, 1, wxRIGHT | wxLEFT | wxBOTTOM | wxEXPAND, 5);
	wxColour dark(74, 74, 74);

	m_projects_list->SetBackgroundColour(dark);
	m_projects_list->SetForegroundColour(wxColour(255, 255, 255));

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
	this->UpdateUsersList();
	this->UpdateProjecstList();

	m_projects_list->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(mw::SidePanel::OnItemSelect), NULL, this);
	m_projects_list->Connect(wxEVT_RIGHT_UP, wxCommandEventHandler(mw::SidePanel::OnProjectListRightUp), NULL, this);
	m_users_choice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(mw::SidePanel::OnUserChange), NULL, this);
	m_new_project_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::SidePanel::OnNewProjectButton), NULL, this);

}

mw::SidePanel::~SidePanel()
{
	m_projects_list->Disconnect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(mw::SidePanel::OnItemSelect), NULL, this);
	m_projects_list->Disconnect(wxEVT_RIGHT_UP, wxCommandEventHandler(mw::SidePanel::OnProjectListRightUp), NULL, this);
	m_users_choice->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(mw::SidePanel::OnUserChange), NULL, this);
	m_new_project_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::SidePanel::OnNewProjectButton), NULL, this);
}
