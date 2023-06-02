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

void mw::SidePanel::UpdateProjectsTree()
{
	mw::Logger logger;
	m_project_tree->Disconnect(wxEVT_TREE_SEL_CHANGED, wxTreeEventHandler(mw::SidePanel::OnProjectSelect), nullptr, this);

	m_project_tree->DeleteAllItems();
	m_tree_item_id_to_project_map.clear();
	wxTreeItemId rootId = m_project_tree->AddRoot("Projects");

	wxTreeItemId itemId;
	mw::Controller& controller = mw::Controller::Get();
	std::vector<mw::Project> projects;
	controller.GetProjectsForActiveUser(projects);
	wxString project_name;

	for (int i = 0; i < projects.size(); i++)
	{
		project_name = projects[i].name;

		itemId = m_project_tree->AppendItem(rootId, project_name);

		m_tree_item_id_to_project_map[itemId] = projects[i];

		if (projects[i].is_active == true)
		{
			m_project_tree->SetItemBold(itemId);
			//warning SelectItem will trigger a selection change event
			m_project_tree->SelectItem(itemId);
		}
	}
	m_project_tree->Connect(wxEVT_TREE_SEL_CHANGED, wxTreeEventHandler(mw::SidePanel::OnProjectSelect), nullptr, this);
}

void mw::SidePanel::OnUpdateUI(wxEvent& event)
{
	this->UpdateUsersList();
	this->UpdateProjectsTree();
}

void mw::SidePanel::OnNewProjectButton(wxCommandEvent& event)
{
	mw::NewProjectFrame* new_project_form = new mw::NewProjectFrame(this);
	new_project_form->CenterOnScreen();
	new_project_form->Show(true);
	event.Skip();
}

void mw::SidePanel::OnUserChange(wxCommandEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	int idx = m_users_choice->GetSelection();
	controller.SetActiveUser(m_idx_to_user[idx]);
	event.Skip();
}

void mw::SidePanel::OnProjectSelect(wxTreeEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	wxTreeItemId id = event.GetItem();
	controller.SetActiveProject(m_tree_item_id_to_project_map[id]);
	event.Skip();
}

void mw::SidePanel::OnProjectLabelChange(wxTreeEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	wxTreeItemId item_id = event.GetItem();
	wxString new_label = event.GetLabel();

	if (!new_label.IsEmpty())
	{
		mw::Project project = this->m_tree_item_id_to_project_map[item_id];
		project.name = new_label.ToStdString();
		controller.AddProject(project, false);
	}
	else
	{
		controller.RequestUpdateUI(this->GetId());
	}
}

void mw::SidePanel::OnProjectsTreeChar(wxKeyEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	if (event.GetKeyCode() == WXK_DELETE)
	{
		wxTreeItemId selected_item = m_project_tree->GetSelection();
		if (selected_item.IsOk())
		{
			mw::Project project = m_tree_item_id_to_project_map[selected_item];
			controller.DeleteProject(project);
			m_project_tree->Delete(selected_item);
		}
	}
	else if (event.GetKeyCode() == WXK_F2)
	{
		wxTreeItemId selected_item = m_project_tree->GetSelection();
		m_project_tree->EditLabel(selected_item);
	}
	else
	{
		event.Skip();
	}
}

void mw::SidePanel::OnProjectsTreeRightClick(wxMouseEvent& event)
{
	wxPoint pos = event.GetPosition();
	wxTreeItemId item;
	int flags;
	m_selected_by_righ_click = m_project_tree->HitTest(pos, flags);
	if (m_selected_by_righ_click.IsOk() && (flags & wxTREE_HITTEST_ONITEM))
	{
		wxMenu contextMenu;
		contextMenu.Append(wxID_DELETE, "Delete");
		
		m_project_tree->PopupMenu(&contextMenu, pos);
	}
}

void mw::SidePanel::OnMenuDelete(wxCommandEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();

	if (m_selected_by_righ_click.IsOk())
	{
		mw::Project project = m_tree_item_id_to_project_map[m_selected_by_righ_click];
		controller.DeleteProject(project);
		m_project_tree->Delete(m_selected_by_righ_click);
	}
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

	wxColour dark(74, 74, 74);


	//projects list instantiation 


	m_project_tree = new wxTreeCtrl(m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_EDIT_LABELS | wxTR_SINGLE | wxTR_HAS_BUTTONS);
	m_project_tree->SetBackgroundColour(dark);
	m_project_tree->SetForegroundColour(wxColour(255, 255, 255));

	bSizer21->Add(m_project_tree, 1, wxRIGHT | wxLEFT | wxBOTTOM | wxEXPAND, 5);

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

	m_project_tree->Connect(wxEVT_TREE_SEL_CHANGED, wxTreeEventHandler(mw::SidePanel::OnProjectSelect), nullptr, this);
	m_project_tree->Connect(wxEVT_TREE_END_LABEL_EDIT, wxTreeEventHandler(mw::SidePanel::OnProjectLabelChange), nullptr, this);
	m_project_tree->Connect(wxEVT_CHAR, wxKeyEventHandler(mw::SidePanel::OnProjectsTreeChar), nullptr, this);
	m_project_tree->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(mw::SidePanel::OnProjectsTreeRightClick), nullptr, this);
	this->Connect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(mw::SidePanel::OnMenuDelete), nullptr, this);


	m_users_choice->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(mw::SidePanel::OnUserChange), NULL, this);
	m_new_project_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::SidePanel::OnNewProjectButton), NULL, this);

	controller.RequestUpdateUI(SIDE_PANEL_ID);
}

mw::SidePanel::~SidePanel()
{
	m_new_project_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::SidePanel::OnNewProjectButton), NULL, this);
	m_users_choice->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(mw::SidePanel::OnUserChange), NULL, this);
	this->Disconnect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(mw::SidePanel::OnMenuDelete), nullptr, this);
	m_project_tree->Disconnect(wxEVT_TREE_SEL_CHANGED, wxTreeEventHandler(mw::SidePanel::OnProjectSelect), nullptr, this);
	m_project_tree->Disconnect(wxEVT_TREE_END_LABEL_EDIT, wxTreeEventHandler(mw::SidePanel::OnProjectLabelChange), nullptr, this);
	m_project_tree->Disconnect(wxEVT_CHAR, wxKeyEventHandler(mw::SidePanel::OnProjectsTreeChar), nullptr, this);
	m_project_tree->Disconnect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(mw::SidePanel::OnProjectsTreeRightClick), nullptr, this);

}
