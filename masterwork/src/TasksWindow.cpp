#include "view/TasksWindow.h"
#include "view/WorkPanel.h"
#include <wx/dataview.h>
#include <wx/datetime.h>


mw::TasksWindow::TasksWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxScrolledWindow(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_tasks_sizer = new wxBoxSizer(wxVERTICAL);
	wxColour background = controller.m_backgroud_color;
	wxColour foreground = controller.m_foreground_color;
	wxColour green(0, 136, 135);

	// creating a tool bar
	m_toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TEXT);
	m_new_task_button = new mw::Button(m_toolbar, wxID_ANY, "New Task", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_new_task_button->SetBackgroundColour(background);
	m_new_task_button->SetForegroundColour(green);

	m_toolbar->AddControl(m_new_task_button);
	m_toolbar->SetBackgroundColour(background);
	m_toolbar->SetForegroundColour(foreground);
	m_toolbar->Realize();

	m_tasks_sizer->Add(m_toolbar, 0, wxEXPAND);

	// creating the dataviewlistctrl object to show task data
	m_tasks_data_view_list = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_MULTIPLE | wxDV_HORIZ_RULES);


	wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL); // Define a font with size 12
	m_tasks_data_view_list->SetFont(font);
	m_tasks_data_view_list->SetRowHeight(40);
	

	wxDataViewColumn* m_uid_column = new wxDataViewColumn("uid", new wxDataViewTextRenderer(), 0, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT);
	m_uid_column->SetSortable(true);
	m_tasks_data_view_list->AppendColumn(m_uid_column);

	wxDataViewColumn* m_title_column = new wxDataViewColumn("Title", new wxDataViewTextRenderer(), 1, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT);
	m_title_column->SetSortable(true);
	m_tasks_data_view_list->AppendColumn(m_title_column);
	wxDataViewColumn* m_status_column = new wxDataViewColumn("Status", new wxDataViewTextRenderer(), 2, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT);
	m_status_column->SetSortable(true);
	m_tasks_data_view_list->AppendColumn(m_status_column);
	wxDataViewColumn* m_priority_column = new wxDataViewColumn("Priority", new wxDataViewTextRenderer(), 3, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT);
	m_priority_column->SetSortable(true);
	m_tasks_data_view_list->AppendColumn(m_priority_column);
	wxDataViewColumn* m_due_data_column = new wxDataViewColumn("Due Date", new wxDataViewTextRenderer(), 4, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT);
	m_tasks_data_view_list->AppendColumn(m_due_data_column);

	m_tasks_data_view_list->SetBackgroundColour(background);
	m_tasks_data_view_list->SetForegroundColour(foreground);

	m_tasks_sizer->Add(m_tasks_data_view_list, 5, wxEXPAND, 0);

	//adding the task panel
	m_task_panel = new mw::TaskPanel(this);

	m_tasks_sizer->Add(m_task_panel, 2, wxEXPAND, 0);

	this->SetSizer(m_tasks_sizer);

	
	m_tasks_data_view_list->Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &mw::TasksWindow::OnItemContextMenu, this);
	m_tasks_data_view_list->Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &mw::TasksWindow::OnSelectionChanged, this);
	this->Bind(mwProjectChanged, &mw::TasksWindow::OnProjectChanged, this);
	this->Bind(mwUpdateUI, &mw::TasksWindow::OnUpdateUI, this);
	this->Bind(wxEVT_MENU, &mw::TasksWindow::OnTaskEditClick, this, 0);
	this->Bind(wxEVT_MENU, &mw::TasksWindow::OnTaskArchieveClick, this, 1);
	this->Bind(wxEVT_MENU, &mw::TasksWindow::OnTaskDeleteClick, this, 2);
	m_tasks_data_view_list->Connect(wxEVT_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler(mw::TasksWindow::OnItemActivated), nullptr, this);
	m_toolbar->Bind(wxEVT_TOOL, &mw::TasksWindow::OnToolbarButtonClick, this);
	m_new_task_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::TasksWindow::OnNewTaskButton), NULL, this);
	controller.RequestUpdateUI(winid);
}

mw::TasksWindow::~TasksWindow()
{
	m_tasks_data_view_list->Disconnect(wxEVT_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler(mw::TasksWindow::OnItemActivated), nullptr, this);
	m_new_task_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::TasksWindow::OnNewTaskButton), NULL, this);
}

void mw::TasksWindow::OnUpdateUI(wxEvent& event)
{
	m_index_to_task_map.clear();
	m_tasks_data_view_list->DeleteAllItems();
	std::vector<mw::Task> tasks;
	mw::Controller& controller = mw::Controller::Get();
	controller.GetTasksForActiveProject(tasks);
	for (int i = 0; i < tasks.size(); i++)
	{
		if (tasks[i].uid == m_task_panel->m_task.uid)
		{
			m_task_panel->SetTask(tasks[i]);
		}
		m_index_to_task_map[i] = tasks[i];
		this->AddTask(tasks[i]);
	}
	mw::WorkPanel* parent_work_panel = dynamic_cast<mw::WorkPanel*>(this->GetParent()->GetParent());
	parent_work_panel->UpdateTasksCount(tasks.size());
	m_toolbar->SetBackgroundColour(controller.m_backgroud_color);
	m_toolbar->SetForegroundColour(controller.m_foreground_color);
}

void mw::TasksWindow::OnNewTaskButton(wxCommandEvent& event)
{
	m_task_panel->NewTask();
}

void mw::TasksWindow::OnItemActivated(wxDataViewEvent& event)
{
	int row_index = m_tasks_data_view_list->GetSelectedRow();
	if (row_index != wxNOT_FOUND)
	{
		TaskFrame* m_new_task_frame = new mw::TaskFrame(this);
		m_new_task_frame->SetTask(m_index_to_task_map[row_index]);
		m_new_task_frame->CenterOnScreen();
		m_new_task_frame->Show(true);
	}
	event.Skip();
}

void mw::TasksWindow::OnSelectionChanged(wxDataViewEvent& event)
{
	int row_index = m_tasks_data_view_list->GetSelectedRow();
	if (row_index != wxNOT_FOUND)
	{
		TaskFrame* m_new_task_frame = new mw::TaskFrame(this);
		m_task_panel->SetTask(m_index_to_task_map[row_index]);
	}
	event.Skip();
}

void mw::TasksWindow::OnItemContextMenu(wxDataViewEvent& event)
{
	mw::Controller& controller = mw::Controller::Get();
	std::vector<mw::Project> projects; 
	controller.GetProjectsForActiveUser(projects);

	mw::Project active_project;
	controller.GetActiveProject(active_project);
	wxDataViewItem item = event.GetItem();
	if (item.IsOk())
	{
		wxMenu* move_submenu = new wxMenu;
		wxMenu menu;
		// using wxID_REMOVE to archive tasks
		menu.Append(0, "Edit");
		menu.Append(1, "Archive");
		menu.Append(2, "Delete");

		// Create a submenu for moving tasks
		for (const auto& project : projects) 
		{
			// Append each project as a submenu item
			if (project.uid != active_project.uid)
			{
				move_submenu->Append(3 + project.uid, wxString::FromUTF8(project.name));
				this->Bind(wxEVT_MENU, &mw::TasksWindow::OnTaskMoveClick, this, 3 + project.uid);
			}
		}

		menu.AppendSubMenu(move_submenu, "Move To");
		
		wxPoint pos = event.GetPosition();
		PopupMenu(&menu, pos); // Show the menu and get the ID of the selected item
	}
	event.Skip();
}

void mw::TasksWindow::OnTaskEditClick(wxCommandEvent& event)
{
	int selected_items_count = m_tasks_data_view_list->GetSelectedItemsCount();
	if (selected_items_count == 0)
		return;
	std::vector<mw::Task> tasks_for_editing;
	mw::Controller& controller = mw::Controller::Get();
	this->GetSelectedTasks(tasks_for_editing);

	TaskFrame* new_task_frame;
	for (int i = 0; i < tasks_for_editing.size(); i++)
	{
		if (m_task_to_frame_map.find(tasks_for_editing[i]) == m_task_to_frame_map.end()) 
		{
			new_task_frame = new mw::TaskFrame(this);
			new_task_frame->Bind(wxEVT_CLOSE_WINDOW, &mw::TasksWindow::OnNewTasksFrameCloseEvent, this);
			new_task_frame->SetTask(tasks_for_editing[i]);
			new_task_frame->CenterOnScreen();
			new_task_frame->Show(true);
			m_task_to_frame_map[tasks_for_editing[i]] = new_task_frame;
		}
		else {
			new_task_frame = m_task_to_frame_map[tasks_for_editing[i]];
			new_task_frame->SetFocus();
		}	
	}
}

void mw::TasksWindow::OnTaskDeleteClick(wxCommandEvent& event)
{
	int selected_items_count = m_tasks_data_view_list->GetSelectedItemsCount();
	if (selected_items_count == 0)
	{
		return;
	}
	std::vector<mw::Task> tasks_for_deletion;
	mw::Controller& controller = mw::Controller::Get();
	int answer = 0;
	if (selected_items_count == 1)
	{
		answer = wxMessageBox("Are you sure you want to permanently delete this task?", "Confirm", wxYES_NO, this);
	}
	else if (selected_items_count > 1)
	{
		answer = wxMessageBox("Are you sure you want to permanently delete all the selected tasks?", "Confirm", wxYES_NO, this);
	}

	if (answer == wxYES)
	{
		this->GetSelectedTasks(tasks_for_deletion);
		controller.DeleteTasks(tasks_for_deletion);
	}
}

void mw::TasksWindow::OnTaskArchieveClick(wxCommandEvent& event)
{
	if (m_tasks_data_view_list->GetSelectedItemsCount() == 0)
		return;
	std::vector<mw::Task> tasks_for_archiving;
	mw::Controller& controller = mw::Controller::Get();
	this->GetSelectedTasks(tasks_for_archiving);
	controller.ArchiveTasks(tasks_for_archiving);
}

void mw::TasksWindow::OnTaskMoveClick(wxCommandEvent& event)
{
	
	mw::Controller& controller = mw::Controller::Get();
	// the project uid of the selected projected is embeded in the event id up binding
	int project_uid = event.GetId() - 3;
	mw::Logger logger;
	logger.EnableDebug();
	logger.Debug("project uid = " + std::to_string(project_uid));
	logger.DisableDebug();
	if (m_tasks_data_view_list->GetSelectedItemsCount() == 0)
		return;
	std::vector<mw::Task> tasks_for_moving;
	this->GetSelectedTasks(tasks_for_moving);
	for (int i = 0; i < tasks_for_moving.size(); i++)
	{
		tasks_for_moving[i].project_uid = project_uid;
		controller.AddTask(tasks_for_moving[i]);
	}
	
	
}

void mw::TasksWindow::AddTask(mw::Task& task)
{
	wxVector<wxVariant> data;
	data.push_back(wxVariant(std::to_string(task.uid)));
	data.push_back(wxVariant(task.name));
	data.push_back(wxVariant(task.GetStatus()));
	data.push_back(wxVariant(task.GetPriority()));
	data.push_back(wxVariant(task.GetDeadline()));
	m_tasks_data_view_list->AppendItem(data);
}

void mw::TasksWindow::OnToolbarButtonClick(wxCommandEvent& event)
{
	int tool_id = event.GetId();

	switch (tool_id) {
	case wxID_NEW:	
		break;
	default:
		break;
	}
}

void mw::TasksWindow::OnNewTasksFrameCloseEvent(wxCloseEvent& event)
{
	TaskFrame* closed_frame = dynamic_cast<TaskFrame*>(event.GetEventObject());
	if (closed_frame != nullptr)
	{
		m_task_to_frame_map.erase(closed_frame->GetTask());
	}
	event.Skip();
}

void mw::TasksWindow::OnProjectChanged(wxEvent& event)
{
	if (m_index_to_task_map.size() > 0)
	{
		m_task_panel->SetTask(m_index_to_task_map[0]);
	}
	else
	{
		m_task_panel->NewTask();
	}
}

void mw::TasksWindow::GetSelectedTasks(std::vector<mw::Task>& tasks)
{
	int row_count = m_tasks_data_view_list->GetItemCount();
	for (int i = 0; i < row_count; i++)
	{
		if (m_tasks_data_view_list->IsRowSelected(i))
		{
			tasks.push_back(m_index_to_task_map[i]);
		}
	}
}
