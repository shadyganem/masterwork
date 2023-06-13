#include "view/TasksWindow.h"

BEGIN_EVENT_TABLE(mw::TasksWindow, wxScrolledWindow)
	EVT_CUSTOM(mwUpdateUI, TASKS_WINDOW_ID, mw::TasksWindow::OnUpdateUI)
END_EVENT_TABLE()

mw::TasksWindow::TasksWindow(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	: wxScrolledWindow(parent, winid, pos, size, style, name)
{
	mw::Controller& controller = mw::Controller::Get();
	controller.RegisterEventHandler(winid, this);
	m_tasks_sizer = new wxBoxSizer(wxVERTICAL);
	wxColour background = controller.m_backgroud_color;
	wxColour foreground = controller.m_forground_color;
	wxColour green(0, 136, 135);

	// creating a tool bar
	wxToolBar* toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TEXT);
	m_new_task_button = new mw::Button(toolbar, wxID_ANY, "New Task", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_new_task_button->SetBackgroundColour(background);
	m_new_task_button->SetForegroundColour(green);
	toolbar->AddControl(m_new_task_button);
	toolbar->SetBackgroundColour(background);
	toolbar->SetForegroundColour(foreground);
	toolbar->Realize();

	m_tasks_sizer->Add(toolbar, 0, wxEXPAND);

	// creating the dataviewlistctrl object to show task data
	m_tasks_data_view_list = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_MULTIPLE | wxDV_HORIZ_RULES);
	m_tasks_data_view_list->AppendColumn(new wxDataViewColumn("Title", new wxDataViewTextRenderer(), 0, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_tasks_data_view_list->AppendColumn(new wxDataViewColumn("Status", new wxDataViewTextRenderer(), 1, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_tasks_data_view_list->AppendColumn(new wxDataViewColumn("Due Date", new wxDataViewTextRenderer(), 2, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_tasks_data_view_list->AppendColumn(new wxDataViewColumn("Priority", new wxDataViewTextRenderer(), 3, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_tasks_data_view_list->AppendColumn(new wxDataViewColumn("Last Modified", new wxDataViewTextRenderer(), 4, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT));
	m_tasks_data_view_list->SetBackgroundColour(background);
	m_tasks_data_view_list->SetForegroundColour(foreground);

	m_tasks_sizer->Add(m_tasks_data_view_list, 1, wxEXPAND, 0);

	this->SetSizer(m_tasks_sizer);

	m_tasks_data_view_list->Bind(wxEVT_DATAVIEW_ITEM_CONTEXT_MENU, &mw::TasksWindow::OnItemContextMenu, this);
	m_tasks_data_view_list->Connect(wxEVT_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler(mw::TasksWindow::OnItemActivated), nullptr, this);
	toolbar->Bind(wxEVT_TOOL, &mw::TasksWindow::OnToolbarButtonClick, this);
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
	m_tasks_data_view_list->DeleteAllItems();
	std::vector<mw::Task> tasks;
	mw::Controller& controller = mw::Controller::Get();
	controller.GetTasksForActiveProject(tasks);
	for (int i = 0; i < tasks.size(); i++)
	{
		m_index_to_task_map[i] = tasks[i];
		this->AddTask(tasks[i]);
	}
}

void mw::TasksWindow::OnNewTaskButton(wxCommandEvent& event)
{
	mw::NewTaskFrame* new_task_frame = new mw::NewTaskFrame(this);
	new_task_frame->CenterOnScreen();
	new_task_frame->Show(true);
	//Do not propagate to parent. this will result in double handling of the button click
}

void mw::TasksWindow::OnItemActivated(wxDataViewEvent& event)
{
	wxDataViewItem selectedItem = m_tasks_data_view_list->GetSelection();
	int row_index = m_tasks_data_view_list->GetSelectedRow();
	if (row_index != wxNOT_FOUND)
	{
		NewTaskFrame* m_new_task_frame = new mw::NewTaskFrame(this);
		m_new_task_frame->SetTask(m_index_to_task_map[row_index]);
		m_new_task_frame->CenterOnScreen();
		m_new_task_frame->Show(true);
	}
	event.Skip();
}

void mw::TasksWindow::OnItemContextMenu(wxDataViewEvent& event)
{
	wxDataViewItem item = event.GetItem();
	if (item.IsOk())
	{
		wxMenu menu;
		// using wxID_REMOVE to archive tasks
		menu.Append(wxID_EDIT, "Edit");
		menu.Append(wxID_REMOVE, "Archive");
		menu.Append(wxID_DELETE, "Delete");
		Bind(wxEVT_MENU, &mw::TasksWindow::OnItemEditClick, this, wxID_EDIT);
		Bind(wxEVT_MENU, &mw::TasksWindow::OnTaskArchieveClick, this, wxID_REMOVE);
		Bind(wxEVT_MENU, &mw::TasksWindow::OnTaskDeleteClick, this, wxID_DELETE);
		wxPoint pos = event.GetPosition();
		PopupMenu(&menu, pos);
	}
	event.Skip();
}

void mw::TasksWindow::OnItemEditClick(wxCommandEvent& event)
{
	int selected_items_count = m_tasks_data_view_list->GetSelectedItemsCount();
	if (selected_items_count == 0)
	{
		return;
	}
	std::vector<mw::Task> tasks_for_editing;
	mw::Controller& controller = mw::Controller::Get();
	
	int row_count = m_tasks_data_view_list->GetItemCount();

	for (int i = 0; i < row_count; i++)
	{
		if (m_tasks_data_view_list->IsRowSelected(i))
		{
			tasks_for_editing.push_back(m_index_to_task_map[i]);
		}
	}

	NewTaskFrame* new_task_frame;
	for (int i = 0; i < tasks_for_editing.size(); i++)
	{
		if (m_task_to_frame_map.find(tasks_for_editing[i]) == m_task_to_frame_map.end()) 
		{
			new_task_frame = new mw::NewTaskFrame(this);
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
	tasks_for_editing.clear();
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
		int row_count = m_tasks_data_view_list->GetItemCount();

		for (int i = 0; i < row_count; i++)
		{
			if (m_tasks_data_view_list->IsRowSelected(i))
			{
				tasks_for_deletion.push_back(m_index_to_task_map[i]);
			}
		}
	}
	controller.DeleteTasks(tasks_for_deletion);
}

void mw::TasksWindow::OnTaskArchieveClick(wxCommandEvent& event)
{
	if (m_tasks_data_view_list->GetSelectedItemsCount() == 0)
	{
		return;
	}
	std::vector<mw::Task> tasks_for_archiving;
	mw::Controller& controller = mw::Controller::Get();


	int row_count = m_tasks_data_view_list->GetItemCount();

	for (int i = 0; i < row_count; i++)
	{
		if (m_tasks_data_view_list->IsRowSelected(i))
		{
			tasks_for_archiving.push_back(m_index_to_task_map[i]);
		}
	}
	controller.ArchiveTasks(tasks_for_archiving);
}

void mw::TasksWindow::AddTask(mw::Task& task)
{
	wxVector<wxVariant> data;
	data.push_back(wxVariant(task.name));
	data.push_back(wxVariant(task.GetStatus()));
	data.push_back(wxVariant(task.GetDeadline()));
	data.push_back(wxVariant(task.GetPriority()));
	data.push_back(wxVariant(task.GetLastUpdate()));

	m_tasks_data_view_list->AppendItem(data);
	wxDataViewItem item = m_tasks_data_view_list->GetTopItem();
	m_item_to_task_map[item] = task;
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
	NewTaskFrame* closed_frame = dynamic_cast<NewTaskFrame*>(event.GetEventObject());
	if (closed_frame != nullptr)
	{
		m_task_to_frame_map.erase(closed_frame->GetTask());
	}
	event.Skip();
}

bool mw::TasksWindow::IsTaskBeingEdited(mw::Task& task)
{
	return false;
}
