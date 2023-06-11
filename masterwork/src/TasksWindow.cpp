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

	wxToolBar* toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_TEXT);
	m_new_task_button = new mw::Button(toolbar, wxID_ANY, "New Task", wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_new_task_button->SetBackgroundColour(background);
	m_new_task_button->SetForegroundColour(green);
	toolbar->AddControl(m_new_task_button);
	toolbar->SetBackgroundColour(background);
	toolbar->SetForegroundColour(foreground);
	toolbar->Realize();

	m_tasks_sizer->Add(toolbar, 0, wxEXPAND);

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

	this->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::TasksWindow::OnTaskScrollWindowLeaveWindow), NULL, this);
	m_tasks_data_view_list->Connect(wxEVT_DATAVIEW_ITEM_ACTIVATED, wxDataViewEventHandler(mw::TasksWindow::OnItemActivated), nullptr, this);
	toolbar->Bind(wxEVT_TOOL, &mw::TasksWindow::OnToolbarButtonClick, this);
	m_new_task_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mw::TasksWindow::OnNewTaskButton), NULL, this);

	controller.RequestUpdateUI(winid);
}

mw::TasksWindow::~TasksWindow()
{
	this->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(mw::TasksWindow::OnTaskScrollWindowLeaveWindow));
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

void mw::TasksWindow::OnTaskScrollWindowLeaveWindow(wxMouseEvent& event)
{
	wxRect panel_rect = this->GetScreenRect();
	wxPoint mouse_pos = wxGetMousePosition();
	if (panel_rect.Contains(mouse_pos))
	{
		event.Skip();
		return;
	}


	std::map<mw::TaskPanel*, mw::Task>::iterator it;
	for (it = m_taskpanel_to_task_map.begin(); it != m_taskpanel_to_task_map.end(); ++it)
	{
		it->first->ResetBackGround();
	}
	event.Skip();
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


void mw::TasksWindow::AddTask(mw::Task& task)
{
	wxVector<wxVariant> data;
	data.push_back(wxVariant(task.name));
	data.push_back(wxVariant(task.GetStatus()));
	data.push_back(wxVariant(task.GetEndTime()));
	data.push_back(wxVariant(task.GetPriority()));
	data.push_back(wxVariant(task.GetLastUpdate()));
	m_tasks_data_view_list->AppendItem(data);
}

void mw::TasksWindow::OnToolbarButtonClick(wxCommandEvent& event)
{
	int tool_id = event.GetId();

	switch (tool_id) {
	case wxID_NEW:	
		// Handle the "New" button click
		break;
	default:
		break;
	}
}